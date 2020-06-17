/*
 * This file is Copyright (c) 2010 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 */
#include <stdio.h>
#include <stdbool.h>
#include "gpsd.h"

#if defined(ONCORE_ENABLE) && defined(BINARY_ENABLE)
#include "bits.h"

static char enableEa[] = { 'E', 'a', 1 };
static char enableBb[] = { 'B', 'b', 1 };
static char getfirmware[] = { 'C', 'j' };
/*static char enableEn[] =
    { 'E', 'n', 1, 0, 100, 100, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };*/
/*static char enableAt2[] 	= { 'A', 't', 2, };*/
static unsigned char pollAs[] =
    { 'A', 's', 0x7f, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0x7f, 0xff,
    0xff, 0xff, 0xff
};
static unsigned char pollAt[] = { 'A', 't', 0xff };
static unsigned char pollAy[] = { 'A', 'y', 0xff, 0xff, 0xff, 0xff };
static unsigned char pollBo[] = { 'B', 'o', 0x01 };
static unsigned char pollEn[] = {
    'E', 'n', 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};


/*
 * These routines are specific to this driver
 */

static gps_mask_t oncore_parse_input(struct gps_device_t *);
static gps_mask_t oncore_dispatch(struct gps_device_t *, unsigned char *,
				  size_t);
static gps_mask_t oncore_msg_navsol(struct gps_device_t *, unsigned char *,
				    size_t);
static gps_mask_t oncore_msg_utc_offset(struct gps_device_t *,
					unsigned char *, size_t);
static gps_mask_t oncore_msg_pps_offset(struct gps_device_t *, unsigned char *,
					size_t);
static gps_mask_t oncore_msg_svinfo(struct gps_device_t *, unsigned char *,
				    size_t);
static gps_mask_t oncore_msg_time_raim(struct gps_device_t *, unsigned char *,
				       size_t);
static gps_mask_t oncore_msg_firmware(struct gps_device_t *, unsigned char *,
				      size_t);

/*
 * These methods may be called elsewhere in gpsd
 */
static ssize_t oncore_control_send(struct gps_device_t *, char *, size_t);
static void oncore_event_hook(struct gps_device_t *, event_t);

/*
 * Decode the navigation solution message
 */
static gps_mask_t
oncore_msg_navsol(struct gps_device_t *session, unsigned char *buf,
		  size_t data_len)
{
    gps_mask_t mask;
    unsigned char flags;
    double lat, lon, alt;
    float speed, track, dop;
    unsigned int i, j, st, nsv;
    int Bbused;
    struct tm unpacked_date;

    if (data_len != 76)
	return 0;

    mask = ONLINE_SET;
    gpsd_log(&session->context->errout, LOG_DATA,
	     "oncore NAVSOL - navigation data\n");

    flags = (unsigned char)getub(buf, 72);

    if (flags & 0x20) {
	session->gpsdata.status = STATUS_FIX;
	session->newdata.mode = MODE_3D;
    } else if (flags & 0x10) {
	session->gpsdata.status = STATUS_FIX;
	session->newdata.mode = MODE_2D;
    } else {
	gpsd_log(&session->context->errout, LOG_WARN,
		 "oncore NAVSOL no fix - flags 0x%02x\n", flags);
	session->newdata.mode = MODE_NO_FIX;
	session->gpsdata.status = STATUS_NO_FIX;
    }
    mask |= MODE_SET;

    /* Unless we have seen non-zero utc offset data, the time is GPS time
     * and not UTC time.  Do not use it.
     */
    if (session->context->leap_seconds) {
	unsigned int nsec;
	unpacked_date.tm_mon = (int)getub(buf, 4) - 1;
	unpacked_date.tm_mday = (int)getub(buf, 5);
	unpacked_date.tm_year = (int)getbeu16(buf, 6) - 1900;
	unpacked_date.tm_hour = (int)getub(buf, 8);
	unpacked_date.tm_min = (int)getub(buf, 9);
	unpacked_date.tm_sec = (int)getub(buf, 10);
	unpacked_date.tm_isdst = 0;
	unpacked_date.tm_wday = unpacked_date.tm_yday = 0;
	nsec = (unsigned int) getbeu32(buf, 11);

	session->newdata.time = (timestamp_t)mkgmtime(&unpacked_date) + nsec * 1e-9;
	mask |= TIME_SET;
	gpsd_log(&session->context->errout, LOG_DATA,
		 "oncore NAVSOL - time: %04d-%02d-%02d %02d:%02d:%02d.%09d\n",
		 unpacked_date.tm_year + 1900, unpacked_date.tm_mon + 1,
		 unpacked_date.tm_mday, unpacked_date.tm_hour,
		 unpacked_date.tm_min, unpacked_date.tm_sec, nsec);
    }

    lat = getbes32(buf, 15) / 3600000.0f;
    lon = getbes32(buf, 19) / 3600000.0f;
    alt = getbes32(buf, 23) / 100.0f;
    speed = getbeu16(buf, 31) / 100.0f;
    track = getbeu16(buf, 33) / 10.0f;
    dop = getbeu16(buf, 35) / 10.0f;

    gpsd_log(&session->context->errout, LOG_DATA,
	     "oncore NAVSOL - %lf %lf %.2lfm-%.2lfm | %.2fm/s %.1fdeg dop=%.1f\n",
	     lat, lon, alt, wgs84_separation(lat, lon), speed, track,
	     (float)dop);

    session->newdata.latitude = lat;
    session->newdata.longitude = lon;
    session->gpsdata.separation =
	wgs84_separation(session->newdata.latitude,
			 session->newdata.longitude);
    session->newdata.altitude = alt - session->gpsdata.separation;
    session->newdata.speed = speed;
    session->newdata.track = track;

    mask |= LATLON_SET | ALTITUDE_SET | SPEED_SET | TRACK_SET;

    gpsd_zero_satellites(&session->gpsdata);
    /* Merge the satellite information from the Bb message. */
    Bbused = 0;
    nsv = 0;
    for (i = st = 0; i < 8; i++) {
	int sv, mode, sn, status;
	unsigned int off;

	off = 40 + 4 * i;
	sv = (int)getub(buf, off);
	mode = (int)getub(buf, off + 1);
	sn = (int)getub(buf, off + 2);
	status = (int)getub(buf, off + 3);

	gpsd_log(&session->context->errout, LOG_DATA,
		 "%2d %2d %2d %3d %02x\n", i, sv, mode, sn, status);

	if (sn) {
	    session->gpsdata.skyview[st].PRN = (short)sv;
	    session->gpsdata.skyview[st].ss = (double)sn;
	    for (j = 0; (int)j < session->driver.oncore.visible; j++)
		if (session->driver.oncore.PRN[j] == sv) {
		    session->gpsdata.skyview[st].elevation =
			(short)session->driver.oncore.elevation[j];
		    session->gpsdata.skyview[st].azimuth =
			(short)session->driver.oncore.azimuth[j];
		    Bbused |= 1 << j;
		    break;
		}
	    /* bit 7 of the status word: sat used for position */
	    session->gpsdata.skyview[st].used = false;
	    if (status & 0x80) {
		session->gpsdata.skyview[st].used = true;
		nsv++;
	    }
	    /* bit 2 of the status word: using for time solution */
	    if (status & 0x02)
		mask |= NTPTIME_IS | GOODTIME_IS;
	    /*
	     * The GOODTIME_IS mask bit exists distinctly from TIME_SET exactly
	     * so an OnCore running in time-service mode (and other GPS clocks)
	     * can signal that it's returning time even though no position fixes
	     * have been available.
	     */
	    st++;
	}
    }
    for (j = 0; (int)j < session->driver.oncore.visible; j++)
	if (!(Bbused & (1 << j))) {
	    session->gpsdata.skyview[st].PRN = (short)session->driver.oncore.PRN[j];
	    session->gpsdata.skyview[st].elevation =
		(short)session->driver.oncore.elevation[j];
	    session->gpsdata.skyview[st].azimuth =
		(short)session->driver.oncore.azimuth[j];
	    st++;
	}
    session->gpsdata.skyview_time = session->newdata.time;
    session->gpsdata.satellites_used = (int)nsv;
    session->gpsdata.satellites_visible = (int)st;

    mask |= SATELLITE_SET | USED_IS;

    /* Some messages can only be polled.  As they are not so
     * important, would be enough to poll e.g. one message per cycle.
     */
    (void)oncore_control_send(session, (char *)pollAs, sizeof(pollAs));
    (void)oncore_control_send(session, (char *)pollAt, sizeof(pollAt));
    (void)oncore_control_send(session, (char *)pollAy, sizeof(pollAy));
    (void)oncore_control_send(session, (char *)pollBo, sizeof(pollBo));
    (void)oncore_control_send(session, (char *)pollEn, sizeof(pollEn));

    gpsd_log(&session->context->errout, LOG_DATA,
	     "NAVSOL: time=%.2f lat=%.2f lon=%.2f alt=%.2f speed=%.2f track=%.2f mode=%d status=%d visible=%d used=%d\n",
	     session->newdata.time, session->newdata.latitude,
	     session->newdata.longitude, session->newdata.altitude,
	     session->newdata.speed, session->newdata.track,
	     session->newdata.mode, session->gpsdata.status,
	     session->gpsdata.satellites_used,
	     session->gpsdata.satellites_visible);
    return mask;
}

/**
 * GPS Leap Seconds = UTC offset
 */
static gps_mask_t
oncore_msg_utc_offset(struct gps_device_t *session, unsigned char *buf,
		      size_t data_len)
{
    int utc_offset;

    if (data_len != 8)
	return 0;

    gpsd_log(&session->context->errout, LOG_DATA,
	     "oncore UTCTIME - leap seconds\n");
    utc_offset = (int)getub(buf, 4);
    if (utc_offset == 0)
	return 0;		/* that part of almanac not received yet */

    session->context->leap_seconds = utc_offset;
    session->context->valid |= LEAP_SECOND_VALID;
    return 0;			/* no flag for leap seconds update */
}

/**
 * PPS offset
 */
static gps_mask_t
oncore_msg_pps_offset(struct gps_device_t *session, unsigned char *buf,
		      size_t data_len)
{
    int pps_offset_ns;

    if (data_len != 11)
	return 0;

    gpsd_log(&session->context->errout, LOG_DATA, "oncore PPS offset\n");
    pps_offset_ns = (int)getbes32(buf, 4);

    session->driver.oncore.pps_offset_ns = pps_offset_ns;
    return 0;
}

/**
 * GPS Satellite Info
 */
static gps_mask_t
oncore_msg_svinfo(struct gps_device_t *session, unsigned char *buf,
		  size_t data_len)
{
    unsigned int i, nchan;
    int j;

    if (data_len != 92)
	return 0;

    gpsd_log(&session->context->errout, LOG_DATA,
	     "oncore SVINFO - satellite data\n");
    nchan = (unsigned int)getub(buf, 4);
    gpsd_log(&session->context->errout, LOG_DATA,
	     "oncore SVINFO - %d satellites:\n", nchan);
    /* Then we clamp the value to not read outside the table. */
    if (nchan > 12)
	nchan = 12;
    session->driver.oncore.visible = (int)nchan;
    for (i = 0; i < nchan; i++) {
	/* get info for one channel/satellite */
	unsigned int off = 5 + 7 * i;

	int sv = (int)getub(buf, off);
	int el = (int)getub(buf, off + 3);
	int az = (int)getbeu16(buf, off + 4);

	gpsd_log(&session->context->errout, LOG_DATA,
		 "%2d %2d %2d %3d\n", i, sv, el, az);

	/* Store for use when Ea messages come. */
	session->driver.oncore.PRN[i] = sv;
	session->driver.oncore.elevation[i] = el;
	session->driver.oncore.azimuth[i] = az;
	/* If it has an entry in the satellite list, update it! */
	for (j = 0; j < session->gpsdata.satellites_visible; j++)
	    if (session->gpsdata.skyview[j].PRN == (short)sv) {
		session->gpsdata.skyview[j].elevation = (short)el;
		session->gpsdata.skyview[j].azimuth = (short)az;
	    }
    }

    gpsd_log(&session->context->errout, LOG_DATA,
	     "SVINFO: mask={SATELLITE}\n");
    return SATELLITE_SET;
}

/**
 * GPS Time RAIM
 */
static gps_mask_t
oncore_msg_time_raim(struct gps_device_t *session UNUSED,
		     unsigned char *buf UNUSED, size_t data_len UNUSED)
{
    int sawtooth_ns;

    if (data_len != 69)
	return 0;

    sawtooth_ns = (int)getub(buf, 25);
    gpsd_log(&session->context->errout, LOG_DATA,
	     "oncore PPS sawtooth: %d\n",sawtooth_ns);

    /* session->driver.oncore.traim_sawtooth_ns = sawtooth_ns; */

    return 0;
}

/**
 * GPS Firmware
 */
static gps_mask_t
oncore_msg_firmware(struct gps_device_t *session UNUSED,
		    unsigned char *buf UNUSED, size_t data_len UNUSED)
{
    return 0;
}

#define ONCTYPE(id2,id3) ((((unsigned int)id2)<<8)|(id3))

/**
 * Parse the data from the device
 */
gps_mask_t oncore_dispatch(struct gps_device_t * session, unsigned char *buf,
			   size_t len)
{
    unsigned int type;

    if (len == 0)
	return 0;

    type = ONCTYPE(buf[2], buf[3]);

    /* we may need to dump the raw packet */
    gpsd_log(&session->context->errout, LOG_RAW,
	     "raw Oncore packet type 0x%04x\n", type);

    session->cycle_end_reliable = true;

    switch (type) {
    case ONCTYPE('B', 'b'):
	return oncore_msg_svinfo(session, buf, len);
    case ONCTYPE('E', 'a'):
	return oncore_msg_navsol(session, buf, len) | (CLEAR_IS | REPORT_IS);
    case ONCTYPE('E', 'n'):
	return oncore_msg_time_raim(session, buf, len);
    case ONCTYPE('C', 'j'):
	return oncore_msg_firmware(session, buf, len);
    case ONCTYPE('B', 'o'):
	return oncore_msg_utc_offset(session, buf, len);
    case ONCTYPE('A', 's'):
	return 0;		/* position hold mode */
    case ONCTYPE('A', 't'):
	return 0;		/* position hold position */
    case ONCTYPE('A', 'y'):
	return oncore_msg_pps_offset(session, buf, len);

    default:
	/* FIX-ME: This gets noisy in a hurry. Change once your driver works */
	gpsd_log(&session->context->errout, LOG_WARN,
		 "unknown packet id @@%c%c length %zd\n",
		 type >> 8, type & 0xff, len);
	return 0;
    }
}


/**********************************************************
 *
 * Externally called routines below here
 *
 **********************************************************/

/**
 * Write data to the device, doing any required padding or checksumming
 */
static ssize_t oncore_control_send(struct gps_device_t *session,
				   char *msg, size_t msglen)
{
    size_t i;
    char checksum = 0;

    session->msgbuf[0] = '@';
    session->msgbuf[1] = '@';
    for (i = 0; i < msglen; i++) {
	checksum ^= session->msgbuf[i + 2] = msg[i];
    }
    session->msgbuf[msglen + 2] = checksum;
    session->msgbuf[msglen + 3] = '\r';
    session->msgbuf[msglen + 4] = '\n';
    session->msgbuflen = msglen + 5;

    gpsd_log(&session->context->errout, LOG_PROG,
	     "writing oncore control type %c%c\n", msg[0], msg[1]);
    return gpsd_write(session, session->msgbuf, session->msgbuflen);
}


static void oncore_event_hook(struct gps_device_t *session, event_t event)
{
    if (session->context->readonly)
	return;

    /*
     * Some oncore VP variants that have not been used after long
     * power-down will be silent on startup.  Provoke
     * identification by requesting the firmware version.
     */
    if (event == event_wakeup)
	(void)oncore_control_send(session, getfirmware, sizeof(getfirmware));

    /*
     * FIX-ME: It might not be necessary to call this on reactivate.
     * Experiment to see if the holds its settings through a close.
     */
    if (event == event_identified || event == event_reactivate) {
	(void)oncore_control_send(session, enableEa, sizeof(enableEa));
	(void)oncore_control_send(session, enableBb, sizeof(enableBb));
	/*(void)oncore_control_send(session, enableEn, sizeof(enableEn)); */
	/*(void)oncore_control_send(session,enableAt2,sizeof(enableAt2)); */
	/*(void)oncore_control_send(session,pollAs,sizeof(pollAs)); */
	(void)oncore_control_send(session, (char*)pollBo, sizeof(pollBo));
    }
}

#ifdef TIMEHINT_ENABLE
static double oncore_time_offset(struct gps_device_t *session UNUSED)
{
    /*
     * Only one sentence (NAVSOL) ships time.  0.175 seems best at
     * 9600 for UT+, not sure what the fudge should be at other baud
     * rates or for other models.
     */
    return 0.175;
}
#endif /* TIMEHINT_ENABLE */

static gps_mask_t oncore_parse_input(struct gps_device_t *session)
{
    if (session->lexer.type == ONCORE_PACKET) {
	return oncore_dispatch(session, session->lexer.outbuffer,
			     session->lexer.outbuflen);
#ifdef NMEA0183_ENABLE
    } else if (session->lexer.type == NMEA_PACKET) {
	return nmea_parse((char *)session->lexer.outbuffer, session);
#endif /* NMEA0183_ENABLE */
    } else
	return 0;
}

/* This is everything we export */
/* *INDENT-OFF* */
const struct gps_type_t driver_oncore = {

    .type_name        = "Motorola Oncore",	/* Full name of type */
    .packet_type      = ONCORE_PACKET,		/* numeric packet type */
    .flags	      = DRIVER_STICKY,		/* remember this */
    .trigger          = NULL,			/* identifying response */
    .channels         = 12,			/* device channel count */
    .probe_detect     = NULL,			/* no probe */
    .get_packet       = generic_get,		/* packet getter */
    .parse_packet     = oncore_parse_input,	/* packet parser */
    .rtcm_writer      = gpsd_write,		/* device accepts RTCM */
    .init_query       = NULL,			/* non-perturbing query */
    .event_hook       = oncore_event_hook,	/* lifetime event hook */
#ifdef RECONFIGURE_ENABLE
    .speed_switcher   = NULL,			/* no speed setter */
    .mode_switcher    = NULL,			/* no mode setter */
    .rate_switcher    = NULL,			/* no speed setter */
    .min_cycle        = 1,			/* 1Hz */
#endif /* RECONFIGURE_ENABLE */
#ifdef CONTROLSEND_ENABLE
    /* Control string sender - should provide checksum and headers/trailer */
    .control_send   = oncore_control_send,	/* to send control strings */
#endif /* CONTROLSEND_ENABLE */
#ifdef TIMEHINT_ENABLE
    .time_offset = oncore_time_offset,		/* NTP offset array */
#endif /* TIMEHINT_ENABLE */
};
/* *INDENT-ON* */
#endif /* defined(ONCORE_ENABLE) && defined(BINARY_ENABLE) */
