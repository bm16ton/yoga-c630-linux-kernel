/*
 * Handle the Rockwell binary packet format supported by the old Zodiac chipset
 *
 * Week counters are not limited to 10 bits. It's unknown what
 * the firmware is doing to disambiguate them, if anything; it might just
 * be adding a fixed offset based on a hidden epoch value, in which case
 * unhappy things will occur on the next rollover.
 *
 * This file is Copyright (c) 2010-2018 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 */

#include "gpsd_config.h"  /* must be before all includes */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#include "gpsd.h"
#include "bits.h"
#include "strfuncs.h"

/* Zodiac protocol description uses 1-origin indexing by little-endian word */
#define get16z(buf, n)	( (buf[2*(n)-2])	\
		| (buf[2*(n)-1] << 8))
#define get32z(buf, n)	( (buf[2*(n)-2])	\
		| (buf[2*(n)-1] << 8) \
		| (buf[2*(n)+0] << 16) \
		| (buf[2*(n)+1] << 24))
#define getstringz(to, from, s, e)			\
    (void)memcpy(to, from+2*(s)-2, 2*((e)-(s)+1))

#ifdef ZODIAC_ENABLE
struct header
{
    unsigned short sync;
    unsigned short id;
    unsigned short ndata;
    unsigned short flags;
    unsigned short csum;
};

static unsigned short zodiac_checksum(unsigned short *w, int n)
{
    unsigned short csum = 0;

    while (n-- > 0)
	csum += *(w++);
    return -csum;
}

static ssize_t end_write(int fd, void *d, size_t len)
/* write an array of shorts in little-endian format */
{
    unsigned char buf[BUFSIZ];
    short *data = (short *)d;

    size_t n;
    for (n = 0; n < (size_t)(len/2); n++)
	putle16(buf, n*2, data[n]);
    return write(fd, (char*)buf, len);
}

/* zodiac_spew - Takes a message type, an array of data words, and a length
 * for the array, and prepends a 5 word header (including checksum).
 * The data words are expected to be checksummed.
 */
static ssize_t zodiac_spew(struct gps_device_t *session, unsigned short type,
			   unsigned short *dat, int dlen)
{
    struct header h;
    int i;
    char buf[BUFSIZ];

    h.sync = 0x81ff;
    h.id = (unsigned short)type;
    h.ndata = (unsigned short)(dlen - 1);
    h.flags = 0;
    h.csum = zodiac_checksum((unsigned short *)&h, 4);

    if (!BAD_SOCKET(session->gpsdata.gps_fd)) {
	size_t hlen, datlen;
	hlen = sizeof(h);
	datlen = sizeof(unsigned short) * dlen;
	if (end_write(session->gpsdata.gps_fd, &h, hlen) != (ssize_t) hlen ||
	    end_write(session->gpsdata.gps_fd, dat,
		      datlen) != (ssize_t) datlen) {
	    GPSD_LOG(LOG_INFO, &session->context->errout,
		     "Reconfigure write failed\n");
	    return -1;
	}
    }

    (void)snprintf(buf, sizeof(buf),
		   "%04x %04x %04x %04x %04x",
		   h.sync, h.id, h.ndata, h.flags, h.csum);
    for (i = 0; i < dlen; i++)
	str_appendf(buf, sizeof(buf), " %04x", dat[i]);

    GPSD_LOG(LOG_RAW, &session->context->errout,
	     "Sent Zodiac packet: %s\n", buf);

    return 0;
}

static void send_rtcm(struct gps_device_t *session,
		      const char *rtcmbuf, size_t rtcmbytes)
{
    unsigned short data[34];
    int n = 1 + (int)(rtcmbytes / 2 + rtcmbytes % 2);

    if (session->driver.zodiac.sn++ > 32767)
	session->driver.zodiac.sn = 0;

    memset(data, 0, sizeof(data));
    data[0] = session->driver.zodiac.sn;	/* sequence number */
    memcpy(&data[1], rtcmbuf, rtcmbytes);
    data[n] = zodiac_checksum(data, n);

    (void)zodiac_spew(session, 1351, data, n + 1);
}

static ssize_t zodiac_send_rtcm(struct gps_device_t *session,
				const char *rtcmbuf, size_t rtcmbytes)
{
    while (rtcmbytes > 0) {
	size_t len = (size_t) (rtcmbytes > 64 ? 64 : rtcmbytes);
	send_rtcm(session, rtcmbuf, len);
	rtcmbytes -= len;
	rtcmbuf += len;
    }
    return 1;
}

#define getzword(n)	get16z(session->lexer.outbuffer, n)
#define getzlong(n)	get32z(session->lexer.outbuffer, n)

static gps_mask_t handle1000(struct gps_device_t *session)
/* time-position-velocity report */
{
    gps_mask_t mask;
    struct tm unpacked_date;
    int datum;
    char ts_buf[TIMESPEC_LEN];

    /* ticks                      = getzlong(6); */
    /* sequence                   = getzword(8); */
    /* measurement_sequence       = getzword(9); */
    session->gpsdata.status = (getzword(10) & 0x1c) ? 0 : 1;
    if (session->gpsdata.status != 0)
	session->newdata.mode = (getzword(10) & 1) ? MODE_2D : MODE_3D;
    else
	session->newdata.mode = MODE_NO_FIX;

    /* solution_type                 = getzword(11); */
    session->gpsdata.satellites_used = (int)getzword(12);
    /* polar_navigation              = getzword(13); */
    session->context->gps_week = (unsigned short)getzword(14);
    /* gps_seconds                   = getzlong(15); */
    /* gps_nanoseconds               = getzlong(17); */
    unpacked_date.tm_mday = (int)getzword(19);
    unpacked_date.tm_mon = (int)getzword(20) - 1;
    unpacked_date.tm_year = (int)getzword(21) - 1900;
    unpacked_date.tm_hour = (int)getzword(22);
    unpacked_date.tm_min = (int)getzword(23);
    unpacked_date.tm_sec = (int)getzword(24);
    unpacked_date.tm_isdst = 0;
    session->newdata.time.tv_sec = mkgmtime(&unpacked_date);
    session->newdata.time.tv_nsec = getzlong(25);
    session->newdata.latitude = ((long)getzlong(27)) * RAD_2_DEG * 1e-8;
    session->newdata.longitude = ((long)getzlong(29)) * RAD_2_DEG * 1e-8;
    /*
     * The Rockwell Jupiter TU30-D140 reports altitude as uncorrected height
     * above WGS84 geoid.  The Zodiac binary protocol manual does not
     * specify whether word 31 is geodetic or WGS 84.
     * Here we assume altitude is always wgs84.
     */
    session->newdata.altHAE = ((long)getzlong(31)) * 1e-2;
    session->newdata.geoid_sep = ((short)getzword(33)) * 1e-2;
    session->newdata.speed = (int)getzlong(34) * 1e-2;
    session->newdata.track = (int)getzword(36) * RAD_2_DEG * 1e-3;
    session->newdata.magnetic_var = ((short)getzword(37)) * RAD_2_DEG * 1e-4;
    session->newdata.climb = ((short)getzword(38)) * 1e-2;
    datum = getzword(39);
    datum_code_string(datum, session->newdata.datum,
                      sizeof(session->newdata.datum));
    /*
     * The manual says these are 1-sigma.  Device reports only eph, circular
     * error.  Let gpsd_model_error() do the rest
     */
    session->newdata.eph = (int)getzlong(40) * 1e-2 * GPSD_CONFIDENCE;
    session->newdata.epv = (int)getzlong(42) * 1e-2 * GPSD_CONFIDENCE;
    session->newdata.ept = (int)getzlong(44) * 1e-2 * GPSD_CONFIDENCE;
    session->newdata.eps = (int)getzword(46) * 1e-2 * GPSD_CONFIDENCE;
    /* clock_bias                  = (int)getzlong(47) * 1e-2; */
    /* clock_bias_sd               = (int)getzlong(49) * 1e-2; */
    /* clock_drift                 = (int)getzlong(51) * 1e-2; */
    /* clock_drift_sd              = (int)getzlong(53) * 1e-2; */

    mask = TIME_SET | NTPTIME_IS | LATLON_SET | ALTITUDE_SET | CLIMB_SET |
           SPEED_SET | TRACK_SET | STATUS_SET | MODE_SET |
           HERR_SET | SPEEDERR_SET | VERR_SET;
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "1000: time=%s lat=%.2f lon=%.2f altHAE=%.2f track=%.2f "
             "speed=%.2f climb=%.2f mode=%d status=%d\n",
             timespec_str(&session->newdata.time, ts_buf, sizeof(ts_buf)),
	     session->newdata.latitude,
	     session->newdata.longitude, session->newdata.altHAE,
	     session->newdata.track, session->newdata.speed,
	     session->newdata.climb, session->newdata.mode,
	     session->gpsdata.status);
    return mask;
}

/* Message 1002: Channel Summary Message */
static gps_mask_t handle1002(struct gps_device_t *session)
{
    int i;
    timespec_t ts_tow;

    /* ticks                      = getzlong(6); */
    /* sequence                   = getzword(8); */
    /* measurement_sequence       = getzword(9); */
    int gps_week = getzword(10);
    time_t gps_seconds = getzlong(11);
    long gps_nanoseconds = getzlong(13);
    char ts_buf[TIMESPEC_LEN];

    /* Note: this week counter is not limited to 10 bits. */
    session->context->gps_week = (unsigned short)gps_week;
    session->gpsdata.satellites_used = 0;
    for (i = 0; i < ZODIAC_CHANNELS; i++) {
	int status, prn;
	session->driver.zodiac.Zv[i] = status = (int)getzword(15 + (3 * i));
	session->driver.zodiac.Zs[i] = prn = (int)getzword(16 + (3 * i));

	if (status & 1)
	    session->gpsdata.satellites_used++;

	session->gpsdata.skyview[i].PRN = (short)prn;
	session->gpsdata.skyview[i].ss = (float)getzword(17 + (3 * i));
	session->gpsdata.skyview[i].used = (bool)(status & 1);
    }
    ts_tow.tv_sec = gps_seconds;
    ts_tow.tv_nsec = gps_nanoseconds;
    session->gpsdata.skyview_time = gpsd_gpstime_resolv(session,
						      (unsigned short)gps_week,
						      ts_tow);
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "1002: visible=%d used=%d mask={SATELLITE|USED} time %s\n",
	     session->gpsdata.satellites_visible,
	     session->gpsdata.satellites_used,
             timespec_str(&session->gpsdata.skyview_time, ts_buf,
                          sizeof(ts_buf)));
    return SATELLITE_SET | USED_IS;
}

static gps_mask_t handle1003(struct gps_device_t *session)
/* skyview report */
{
    int i, n;

    /* The Polaris (and probably the DAGR) emit some strange variant of
     * this message which causes gpsd to crash filtering on impossible
     * number of satellites avoids this */
    n = (int)getzword(14);
    if ((n < 0) || (n > 12))
	return 0;

    gpsd_zero_satellites(&session->gpsdata);

    /* ticks              = getzlong(6); */
    /* sequence           = getzword(8); */
    session->gpsdata.dop.gdop = (unsigned int)getzword(9) * 1e-2;
    session->gpsdata.dop.pdop = (unsigned int)getzword(10) * 1e-2;
    session->gpsdata.dop.hdop = (unsigned int)getzword(11) * 1e-2;
    session->gpsdata.dop.vdop = (unsigned int)getzword(12) * 1e-2;
    session->gpsdata.dop.tdop = (unsigned int)getzword(13) * 1e-2;
    session->gpsdata.satellites_visible = n;

    for (i = 0; i < ZODIAC_CHANNELS; i++) {
	if (i < session->gpsdata.satellites_visible) {
	    session->gpsdata.skyview[i].PRN = (short)getzword(15 + (3 * i));
	    session->gpsdata.skyview[i].azimuth =
		(((double)getzword(16 + (3 * i))) * RAD_2_DEG * 1e-4);
	    if (session->gpsdata.skyview[i].azimuth < 0)
		session->gpsdata.skyview[i].azimuth += 360;
	    session->gpsdata.skyview[i].elevation =
		(((double)getzword(17 + (3 * i))) * RAD_2_DEG * 1e-4);
	} else {
	    session->gpsdata.skyview[i].PRN = 0;
	    session->gpsdata.skyview[i].azimuth = NAN;
	    session->gpsdata.skyview[i].elevation = NAN;
	    session->gpsdata.skyview[i].ss = NAN;
	}
    }
    session->gpsdata.skyview_time.tv_sec = 0;
    session->gpsdata.skyview_time.tv_nsec = 0;
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "NAVDOP: visible=%d gdop=%.2f pdop=%.2f "
	     "hdop=%.2f vdop=%.2f tdop=%.2f mask={SATELLITE|DOP}\n",
	     session->gpsdata.satellites_visible,
	     session->gpsdata.dop.gdop,
	     session->gpsdata.dop.hdop,
	     session->gpsdata.dop.vdop,
	     session->gpsdata.dop.pdop, session->gpsdata.dop.tdop);
    return SATELLITE_SET | DOP_SET;
}

static void handle1005(struct gps_device_t *session UNUSED)
/* fix quality report */
{
    /* ticks              = getzlong(6); */
    /* sequence           = getzword(8); */
    int numcorrections = (int)getzword(12);

    if (session->newdata.mode == MODE_NO_FIX)
	session->gpsdata.status = STATUS_NO_FIX;
    else if (numcorrections == 0)
	session->gpsdata.status = STATUS_FIX;
    else
	session->gpsdata.status = STATUS_DGPS_FIX;
}

static gps_mask_t handle1011(struct gps_device_t *session)
/* version report */
{
    /*
     * This is UNTESTED -- but harmless if buggy.  Added to support
     * client querying of the ID with firmware version in 2006.
     * The Zodiac is supposed to send one of these messages on startup.
     */
    getstringz(session->subtype, session->lexer.outbuffer, 19, 28);	/* software version field */
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "1011: subtype=%s mask={DEVICEID}\n",
	     session->subtype);
    return DEVICEID_SET;
}


static void handle1108(struct gps_device_t *session)
/* leap-second correction report */
{
    /* ticks              = getzlong(6); */
    /* sequence           = getzword(8); */
    /* utc_week_seconds   = getzlong(14); */
    /* leap_nanoseconds   = getzlong(17); */
    if ((int)(getzword(19) & 3) == 3) {
	session->context->valid |= LEAP_SECOND_VALID;
	session->context->leap_seconds = (int)getzword(16);
    }
}

static gps_mask_t zodiac_analyze(struct gps_device_t *session)
{
    unsigned int id =
	(unsigned int)((session->lexer.outbuffer[3] << 8) |
		       session->lexer.outbuffer[2]);
    /*
     * The guard looks superfluous, but it keeps the rather expensive
     * gpsd_packetdump() function from being called even when the debug
     * level does not actually require it.
     */
    if (session->context->errout.debug >= LOG_RAW)
	GPSD_LOG(LOG_RAW, &session->context->errout,
		 "Raw Zodiac packet type %d length %zd: %s\n",
		 id, session->lexer.outbuflen, gpsd_prettydump(session));

    if (session->lexer.outbuflen < 10)
	return 0;

    /*
     * Normal cycle for these devices is 1001 1002.
     * We count 1001 as end of cycle because 1002 doesn't
     * carry fix information.
     */
    session->cycle_end_reliable = true;

    switch (id) {
    case 1000:
	return handle1000(session) | (CLEAR_IS | REPORT_IS);
    case 1002:
	return handle1002(session);
    case 1003:
	return handle1003(session);
    case 1005:
	handle1005(session);
	return 0;
    case 1011:
	return handle1011(session);
    case 1108:
	handle1108(session);
	return 0;
    default:
	return 0;
    }
}

#ifdef CONTROLSEND_ENABLE
static ssize_t zodiac_control_send(struct gps_device_t *session,
				   char *msg, size_t len)
{
    unsigned short shortwords[256];

#define min(x,y)	((x) < (y) ? x : y)
    /*
     * We used to just cast msg to an unsigned short pointer.
     * This can fail on word-oriented achitectures like a SPARC.
     */
    memcpy((char *)shortwords, msg, min(sizeof(shortwords), len));

    /* and if len isn't even, it's your own fault */
    return zodiac_spew(session, shortwords[0], shortwords + 1,
		       (int)(len / 2 - 1));
}
#endif /* CONTROLSEND_ENABLE */

#ifdef RECONFIGURE_ENABLE
static bool zodiac_speed_switch(struct gps_device_t *session,
				speed_t speed, char parity, int stopbits)
{
    unsigned short data[15];

    if (session->driver.zodiac.sn++ > 32767)
	session->driver.zodiac.sn = 0;

    switch (parity) {
    case 'E':
    case 2:
	parity = (char)2;
	break;
    case 'O':
    case 1:
	parity = (char)1;
	break;
    case 'N':
    case 0:
    default:
	parity = (char)0;
	break;
    }

    memset(data, 0, sizeof(data));
    /* data is the part of the message starting at word 6 */
    data[0] = session->driver.zodiac.sn;	/* sequence number */
    data[1] = 1;		/* port 1 data valid */
    data[2] = (unsigned short)parity;	/* port 1 character width (8 bits) */
    data[3] = (unsigned short)(stopbits - 1);	/* port 1 stop bits (1 stopbit) */
    data[4] = 0;		/* port 1 parity (none) */
    data[5] = (unsigned short)(round(log((double)speed / 300) / GPS_LN2) + 1);	/* port 1 speed */
    data[14] = zodiac_checksum(data, 14);

    (void)zodiac_spew(session, 1330, data, 15);
    return true;		/* it would be nice to error-check this */
}
#endif /* RECONFIGURE_ENABLE */

static double zodiac_time_offset(struct gps_device_t *session UNUSED)
{
    /* Removing/changing the magic number below is likely to disturb
     * the handling of the 1pps signal from the gps device. The regression
     * tests and simple gps applications do not detect this. A live test
     * with the 1pps signal active is required. */
    return 1.1;
}

/* this is everything we export */
/* *INDENT-OFF* */
const struct gps_type_t driver_zodiac =
{
    .type_name      = "Zodiac",		/* full name of type */
    .packet_type    = ZODIAC_PACKET,	/* associated lexer packet type */
    .flags	    = DRIVER_STICKY,	/* no flags set */
    .trigger	    = NULL,		/* no trigger */
    .channels       = 12,		/* consumer-grade GPS */
    .probe_detect   = NULL,		/* no probe */
    .get_packet     = generic_get,	/* use the generic packet getter */
    .parse_packet   = zodiac_analyze,	/* parse message packets */
    .rtcm_writer    = zodiac_send_rtcm,	/* send DGPS correction */
    .init_query     = NULL,		/* non-perturbing initial query */
    .event_hook     = NULL,		/* no configuration */
#ifdef RECONFIGURE_ENABLE
    .speed_switcher = zodiac_speed_switch,/* we can change baud rate */
    .mode_switcher  = NULL,		/* no mode switcher */
    .rate_switcher  = NULL,		/* no sample-rate switcher */
    .min_cycle.tv_sec  = 1,		/* not relevant, no rate switch */
    .min_cycle.tv_nsec = 0,		/* not relevant, no rate switch */
#endif /* RECONFIGURE_ENABLE */
#ifdef CONTROLSEND_ENABLE
    .control_send   = zodiac_control_send,	/* for gpsctl and friends */
#endif /* CONTROLSEND_ENABLE */
    .time_offset     = zodiac_time_offset,	/* compute NTO fudge factor */
};
/* *INDENT-ON* */

#endif /* ZODIAC_ENABLE */
