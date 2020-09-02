/*
 * This file is Copyright (c) 2010-2019 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 */
#include "gpsd_config.h"  /* must be before all includes */

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "gpsd.h"

#if defined(SUPERSTAR2_ENABLE) && defined(BINARY_ENABLE)
#include "bits.h"
#include "driver_superstar2.h"
#include "timespec.h"

/*
 * These routines are specific to this driver
 */

static gps_mask_t superstar2_parse_input(struct gps_device_t *);
static gps_mask_t superstar2_dispatch(struct gps_device_t *,
				      unsigned char *, size_t);
static gps_mask_t superstar2_msg_ack(struct gps_device_t *,
				     unsigned char *, size_t);
static gps_mask_t superstar2_msg_navsol_lla(struct gps_device_t *,
					    unsigned char *, size_t);
static gps_mask_t superstar2_msg_timing(struct gps_device_t *,
					unsigned char *, size_t);
static gps_mask_t superstar2_msg_svinfo(struct gps_device_t *,
					unsigned char *, size_t);
static gps_mask_t superstar2_msg_iono_utc(struct gps_device_t *,
					  unsigned char *, size_t);
static gps_mask_t superstar2_msg_ephemeris(struct gps_device_t *,
					   unsigned char *, size_t);

/*
 * These methods may be called elsewhere in gpsd
 */
#ifdef CONTROLSEND_ENABLE
static ssize_t superstar2_control_send(struct gps_device_t *, char *, size_t);
#endif /* CONTROLSEND_ENABLE */
static void superstar2_event_hook(struct gps_device_t *, event_t);
static ssize_t superstar2_write(struct gps_device_t *, char *, size_t);
#ifdef RECONFIGURE_ENABLE
static bool superstar2_set_speed(struct gps_device_t *, speed_t, char, int);
static void superstar2_set_mode(struct gps_device_t *, int);
#endif /* RECONFIGURE_ENABLE */


/*
 * Decode the message ACK message
 */
static gps_mask_t
superstar2_msg_ack(struct gps_device_t *session,
		   unsigned char *buf, size_t data_len)
{
    if (data_len == 11)
	GPSD_LOG(LOG_PROG, &session->context->errout,
		 "superstar2 #126 - ACK %d %d %d %d %d\n",
		 buf[5], buf[6], buf[7], buf[8], buf[9]);
    return 0;
}

/*
 * Decode the navigation solution message. The ECEF version is intentionally
 * unhandled. By suppressing evaluation of it, we gain the desirable feature
 * that the fix update is atomic and exactly once per cycle.
 */


/* Navigation Data (User Coordinates) ID# 20 */
static gps_mask_t
superstar2_msg_navsol_lla(struct gps_device_t *session,
			  unsigned char *buf, size_t data_len)
{
    gps_mask_t mask;
    unsigned char flags;
    double d;
    struct tm tm;
    double int_part;
    char ts_buf[TIMESPEC_LEN];

    if (data_len != 77)
	return 0;

    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "superstar2 #20 - user navigation data\n");
    mask = 0;

    flags = (unsigned char)getub(buf, 72);
    if ((flags & 0x0f) != 0x03)	/* mode 3 is navigation */
	return mask;

    /* extract time data */
    (void)memset(&tm, '\0', sizeof(tm));
    tm.tm_hour = (int)getub(buf, 4) & 0x1f;
    tm.tm_min = (int)getub(buf, 5);
    d = getled64((char *)buf, 6);           /* seconds as a double */
    session->newdata.time.tv_nsec = (long)(modf(d, &int_part) * 1e9);
    tm.tm_sec = (int)int_part;
    tm.tm_mday = (int)getub(buf, 14);
    tm.tm_mon = (int)getub(buf, 15) - 1;
    tm.tm_year = (int)getleu16(buf, 16) - 1900;
    tm.tm_isdst = 0;
    session->newdata.time.tv_sec = mkgmtime(&tm);
    mask |= TIME_SET | NTPTIME_IS;

    /* extract the local tangential plane (ENU) solution */
    session->newdata.latitude = getled64((char *)buf, 18) * RAD_2_DEG;
    session->newdata.longitude = getled64((char *)buf, 26) * RAD_2_DEG;
    /* unclear if this is MSL or WGS84.  Assume WGS84 */
    session->newdata.altHAE = getlef32((char *)buf, 34);
    session->newdata.speed = getlef32((char *)buf, 38);
    session->newdata.track = getlef32((char *)buf, 42) * RAD_2_DEG;
    session->newdata.climb = getlef32((char *)buf, 54);
    mask |= LATLON_SET | ALTITUDE_SET | SPEED_SET | TRACK_SET | CLIMB_SET;

    session->gpsdata.satellites_used = (int)getub(buf, 71) & 0x0f;
    session->gpsdata.dop.hdop = getleu16(buf, 66) * 0.1;
    session->gpsdata.dop.vdop = getleu16(buf, 68) * 0.1;
    /* other DOP if available */
    mask |= DOP_SET | USED_IS;

    flags = (unsigned char)getub(buf, 70);
    switch (flags & 0x1f) {
    case 2:
	session->newdata.mode = MODE_3D;
	session->gpsdata.status = STATUS_FIX;
	break;
    case 4:
	session->newdata.mode = MODE_3D;
	session->gpsdata.status = STATUS_DGPS_FIX;
	break;
    case 5:
	session->newdata.mode = MODE_2D;
	session->gpsdata.status = STATUS_DGPS_FIX;
	break;
    case 3:
    case 6:
	session->newdata.mode = MODE_2D;
	session->gpsdata.status = STATUS_FIX;
	break;
    default:
	session->gpsdata.status = STATUS_NO_FIX;
	session->newdata.mode = MODE_NO_FIX;
    }

    mask |= MODE_SET | STATUS_SET;
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "NAVSOL_LLA: time=%s lat=%.2f lon=%.2f altHAE=%.2f "
             "track=%.2f speed=%.2f climb=%.2f mode=%d status=%d hdop=%.2f "
             "hdop=%.2f used=%d\n",
             timespec_str(&session->newdata.time, ts_buf, sizeof(ts_buf)),
	     session->newdata.latitude,
	     session->newdata.longitude,
	     session->newdata.altHAE,
	     session->newdata.track,
	     session->newdata.speed,
	     session->newdata.climb,
	     session->newdata.mode,
	     session->gpsdata.status,
	     session->gpsdata.dop.hdop,
	     session->gpsdata.dop.vdop,
	     session->gpsdata.satellites_used);
    return mask;
}

/*
 * GPS Satellite Info
 */
static gps_mask_t
superstar2_msg_svinfo(struct gps_device_t *session,
		      unsigned char *buf, size_t data_len)
{
    int i, st, nchan, nsv;

    if (data_len != 67)
	return 0;

    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "superstar2 #33 - satellite data\n");

    nchan = 12;
    gpsd_zero_satellites(&session->gpsdata);
    nsv = 0;			/* number of actually used satellites */
    for (i = st = 0; i < nchan; i++) {
	/* get info for one channel/satellite */
	int off = i * 5 + 5;
	unsigned int porn;
	bool used = (getub(buf, off) & 0x60) == 0x60;
	if ((porn = (unsigned int)getub(buf, off) & 0x1f) == 0)
	    porn = (unsigned int)(getub(buf, off + 3) >> 1) + 87;

	session->gpsdata.skyview[i].PRN = (short)porn;
	session->gpsdata.skyview[i].ss = (double)getub(buf, off + 4);
	session->gpsdata.skyview[i].elevation = (double)getsb(buf, off + 1);
	session->gpsdata.skyview[i].azimuth = (double)getub(buf, off + 2) +
	    (short)((unsigned short)(getub(buf, off + 3) & 0x1) << 1);
	session->gpsdata.skyview[i].used = used;
	if (used)
	    nsv++;

	if (session->gpsdata.skyview[i].PRN)
	    st++;
    }
    session->gpsdata.skyview_time.tv_sec = 0;
    session->gpsdata.skyview_time.tv_nsec = 0;
    session->gpsdata.satellites_used = nsv;
    session->gpsdata.satellites_visible = st;
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "SVINFO: visible=%d used=%d mask={SATELLITE|USED}\n",
	     session->gpsdata.satellites_visible,
	     session->gpsdata.satellites_used);
    return SATELLITE_SET | USED_IS;
}

static gps_mask_t
superstar2_msg_version(struct gps_device_t *session,
		       unsigned char *buf, size_t data_len)
{
#define SZ 16
    char main_sw[SZ], hw_part[SZ], boot_sw[SZ], ser_num[SZ];

    /* byte 98 is device type, value = 3 means superstar2 */
    if ((data_len != 101) || ((getub(buf, 98) & 0x0f) != 3))
	return 0;

    (void)snprintf(main_sw, 15, "%s", (char *)buf + 4);
    (void)snprintf(hw_part, 15, "%s", (char *)buf + 18);
    (void)snprintf(boot_sw, 15, "%s", (char *)buf + 36);
    (void)snprintf(ser_num, 14, "%s", (char *)buf + 73);

    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "superstar2 #45 - hw part %s boot sw %s main sw %s ser num %s\n",
	     hw_part, boot_sw, main_sw, ser_num);
    (void)strlcpy(session->subtype, main_sw, sizeof(session->subtype));
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "VERSION: subtype='%s' mask={DEVEICEID}\n",
	     session->subtype);
    return DEVICEID_SET;
}

/**
 * Timing Status ID# 113
 *
 * Precise Timing models only
 */
static gps_mask_t
superstar2_msg_timing(struct gps_device_t *session, unsigned char *buf,
		      size_t data_len)
{
    gps_mask_t mask;
    struct tm tm;

    if (data_len != 65)
	return 0;

    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "superstar2 #113 - timing status\n");
    if ((getub(buf, 55) & 0x30) != 0)
	mask = 0;
    else {
	double d;
	/* extract time data */
	(void)memset(&tm, '\0', sizeof(tm));
	tm.tm_mday = (int)getsb(buf, 37);
	tm.tm_mon = (int)getsb(buf, 38) - 1;
	tm.tm_year = (int)getles16(buf, 39) - 1900;

	tm.tm_hour = (int)getsb(buf, 41);
	tm.tm_min = (int)getsb(buf, 42);
	d = getled64((char *)buf, 43);
	tm.tm_sec = (int)d;
	tm.tm_isdst = 0;
	session->newdata.time.tv_sec = mkgmtime(&tm);
	session->newdata.time.tv_nsec = 0;
	session->context->leap_seconds = (int)getsb(buf, 20);
	mask = TIME_SET | NTPTIME_IS;
    }
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "TIMING: time=%lld mask={TIME}\n",
	     (long long)session->newdata.time.tv_sec);
    return mask;
}

/**
 * Raw Measurements
 */
static gps_mask_t
superstar2_msg_measurement(struct gps_device_t *session, unsigned char *buf,
			   size_t data_len UNUSED)
{
    gps_mask_t mask = 0;
    int i, n;
    double t;

    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "superstar2 #23 - measurement block\n");

    n = (int)getub(buf, 6);	/* number of measurements */
    if ((n < 1) || (n > MAXCHANNELS)) {
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "too many measurements\n");
	return 0;
    }
    t = getled64((char *)buf, 7);		/* measurement time */
    DTOTS(&session->gpsdata.raw.mtime, t);

    /* this is so we can tell which never got set */
    for (i = 0; i < MAXCHANNELS; i++)
        session->gpsdata.raw.meas[i].svid = 0;
    for (i = 0; i < n; i++) {
	unsigned long ul;
	session->gpsdata.skyview[i].PRN =
            (short)(getub(buf, 11 * i + 15) & 0x1f);
	session->gpsdata.skyview[i].ss =
            (double)getub(buf, 11 * i * 15 + 1) / 4.0;
	session->gpsdata.raw.meas[i].codephase =
	    (double)getleu32(buf, 11 * i * 15 + 2);
	ul = (unsigned long)getleu32(buf, 11 * i * 15 + 6);

	session->gpsdata.raw.meas[i].satstat = (unsigned int)(ul & 0x03L);
	session->gpsdata.raw.meas[i].carrierphase =
            (double)((ul >> 2) & 0x03ffL);
	session->gpsdata.raw.meas[i].pseudorange = (double)(ul >> 12);
    }

    /*The above decode does not look correct, do not report */
    /* mask |= RAW_IS; */
    return mask;
}

/* request for ionospheric and utc time data #75 */
static unsigned char iono_utc_msg[] = { 0x01, 0x4b, 0xb4, 0x00, 0x00, 0x01 };



/**
 * Ionospheric/UTC parameters
 */
static gps_mask_t
superstar2_msg_iono_utc(struct gps_device_t *session, unsigned char *buf,
			size_t data_len UNUSED)
{
    unsigned int i, u;

    i = (unsigned int)getub(buf, 12);
    u = (unsigned int)getub(buf, 21);
    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "superstar2 #75 - ionospheric & utc data: iono %s utc %s\n",
	     i ? "ok" : "bad", u ? "ok" : "bad");
    session->driver.superstar2.last_iono = time(NULL);

    return 0;
}


/**
 * Ephemeris
 */
static gps_mask_t
superstar2_msg_ephemeris(struct gps_device_t *session, unsigned char *buf,
			 size_t data_len UNUSED)
{
    unsigned int prn;
    prn = (unsigned int)(getub(buf, 4) & 0x1f);
    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "superstar2 #22 - ephemeris data - prn %u\n", prn);

    /* ephemeris data updates fairly slowly, but when it does, poll UTC */
    if ((time(NULL) - session->driver.superstar2.last_iono) > 60)
	(void)superstar2_write(session, (char *)iono_utc_msg,
			       sizeof(iono_utc_msg));

    return ONLINE_SET;
}


static ssize_t
superstar2_write(struct gps_device_t *session, char *msg, size_t msglen)
{
    unsigned short c = 0;
    ssize_t i;

    for (i = 0; i < (ssize_t) (msglen - 2); i++)
	c += (unsigned short)msg[i];
    c += 0x100;
    msg[(int)msg[3] + 4] = (char)((c >> 8) & 0xff);
    msg[(int)msg[3] + 5] = (char)(c & 0xff);
    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "writing superstar2 control type %d len %zu\n",
	     (int)msg[1] & 0x7f, msglen);
    return gpsd_write(session, msg, msglen);
}

/**
 * Parse the data from the device
 */
gps_mask_t
superstar2_dispatch(struct gps_device_t * session, unsigned char *buf,
		    size_t len)
{
    int type;

    if (len == 0)
	return 0;

    type = (int)buf[SUPERSTAR2_TYPE_OFFSET];
    session->cycle_end_reliable = true;

    switch (type) {
    case SUPERSTAR2_ACK:	/* Message Acknowledgement */
	return superstar2_msg_ack(session, buf, len);
    case SUPERSTAR2_SVINFO:	/* Satellite Visibility Data */
	return superstar2_msg_svinfo(session, buf, len);
    case SUPERSTAR2_NAVSOL_LLA:	/* Navigation Data */
	return superstar2_msg_navsol_lla(session, buf,
					 len) | (CLEAR_IS | REPORT_IS);
    case SUPERSTAR2_VERSION:	/* Hardware/Software Version */
	return superstar2_msg_version(session, buf, len);
    case SUPERSTAR2_TIMING:	/* Timing Parameters */
	return superstar2_msg_timing(session, buf, len);
    case SUPERSTAR2_MEASUREMENT:	/* Timing Parameters */
	return superstar2_msg_measurement(session, buf, len);
    case SUPERSTAR2_IONO_UTC:
	return superstar2_msg_iono_utc(session, buf, len);
    case SUPERSTAR2_EPHEMERIS:
	return superstar2_msg_ephemeris(session, buf, len);

    default:
	GPSD_LOG(LOG_WARN, &session->context->errout,
		 "unknown superstar2 packet id 0x%02x length %zd\n",
		 type, len);
	return 0;
    }
}

/**********************************************************
 *
 * Externally called routines below here
 *
 **********************************************************/

static void superstar2_event_hook(struct gps_device_t *session, event_t event)
{
    if (session->context->readonly)
	return;

    if (event == event_identified) {
	unsigned char version_msg[]    = { 0x01, 0x2d, 0xd2, 0x00, 0x00, 0x01 };
	unsigned char svinfo_msg[]     = { 0x01, 0xa1, 0x5e, 0x00, 0x00, 0x01 };
	unsigned char timing_msg[]     = { 0x01, 0xf1, 0x0e, 0x00, 0x00, 0x01 };
	unsigned char navsol_lla_msg[] = { 0x01, 0x94, 0x6b, 0x00, 0x00, 0x01 };
	unsigned char ephemeris_msg[]  = { 0x01, 0x96, 0x69, 0x00, 0x00, 0x01 };
	unsigned char measurement_msg[] =
	    { 0x01, 0x97, 0x68, 0x01, 0x00, 0x01, 0x01 };

	(void)superstar2_write(session, (char *)timing_msg,
			       sizeof(timing_msg));
	(void)superstar2_write(session, (char *)measurement_msg,
			       sizeof(measurement_msg));
	(void)superstar2_write(session, (char *)svinfo_msg,
			       sizeof(svinfo_msg));
	(void)superstar2_write(session, (char *)navsol_lla_msg,
			       sizeof(navsol_lla_msg));
	(void)superstar2_write(session, (char *)version_msg,
			       sizeof(version_msg));
	(void)superstar2_write(session, (char *)ephemeris_msg,
			       sizeof(ephemeris_msg));
	(void)superstar2_write(session, (char *)iono_utc_msg,
			       sizeof(iono_utc_msg));
	session->driver.superstar2.last_iono = time(NULL);
    }
}

/*
 * This is the entry point to the driver. When the packet sniffer recognizes
 * a packet for this driver, it calls this method which passes the packet to
 * the binary processor or the nmea processor, depending on the session type.
 */
static gps_mask_t superstar2_parse_input(struct gps_device_t *session)
{
    if (session->lexer.type == SUPERSTAR2_PACKET) {
	return superstar2_dispatch(session, session->lexer.outbuffer,
				   session->lexer.length);;
#ifdef NMEA0183_ENABLE
    } else if (session->lexer.type == NMEA_PACKET) {
	return nmea_parse((char *)session->lexer.outbuffer, session);
#endif /* NMEA0183_ENABLE */
    } else
	return 0;
}

#ifdef CONTROLSEND_ENABLE
static ssize_t
superstar2_control_send(struct gps_device_t *session, char *msg,
			size_t msglen)
{
    session->msgbuf[0] = 0x1;	/* SOH */
    session->msgbuf[1] = msg[0];
    session->msgbuf[2] = msg[0] ^ 0xff;
    session->msgbuf[3] = (char)(msglen + 1);
    (void)memcpy(session->msgbuf + 4, msg + 1, msglen - 1);
    session->msgbuflen = (size_t) (msglen + 5);
    return superstar2_write(session, session->msgbuf, session->msgbuflen);
}
#endif /* CONTROLSEND_ENABLE */

#ifdef RECONFIGURE_ENABLE
static bool superstar2_set_speed(struct gps_device_t *session,
				 speed_t speed, char parity, int stopbits)
{
    /* parity and stopbit switching aren't available on this chip */
    if (parity != session->gpsdata.dev.parity
	|| stopbits != (int)session->gpsdata.dev.stopbits) {
	return false;
    } else {
	unsigned char speed_msg[] =
	    { 0x01, 0x48, 0xB7, 0x01, 0x00, 0x00, 0x00 };

	/* high bit 0 in the mode word means set NMEA mode */
	speed_msg[4] = (unsigned char)(speed / 300);
	return (superstar2_write(session, (char *)speed_msg, 7) == 7);
    }
}

static void superstar2_set_mode(struct gps_device_t *session, int mode)
{
    if (mode == MODE_NMEA) {
	unsigned char mode_msg[] =
	    { 0x01, 0x48, 0xB7, 0x01, 0x00, 0x00, 0x00 };

	/* high bit 0 in the mode word means set NMEA mode */
	mode_msg[4] = (unsigned char)(session->gpsdata.dev.baudrate / 300);
	(void)superstar2_write(session, (char *)mode_msg, 7);
    }
}
#endif /* RECONFIGURE_ENABLE */

/* *INDENT-OFF* */
const struct gps_type_t driver_superstar2 = {
    /* Full name of type */
    .type_name		= "SuperStarII",
    /* Associated lexer packet type */
    .packet_type        = SUPERSTAR2_PACKET,
    /* Driver type flags */
    .flags	         = DRIVER_STICKY,
    /* Response string that identifies device (not active) */
    .trigger		= NULL,
    /* Number of satellite channels supported by the device */
    .channels	 	= 12,
    /* Startup-time device detector */
    .probe_detect	= NULL,
    /* Packet getter (using default routine) */
    .get_packet		= generic_get,
    /* Parse message packets */
    .parse_packet	= superstar2_parse_input,
    /* RTCM handler (using default routine) */
    .rtcm_writer	= gpsd_write,
    /* non-perturbing initial query */
    .init_query         = NULL,
    /* Fire on various lifetime events */
    .event_hook		= superstar2_event_hook,
#ifdef RECONFIGURE_ENABLE
    /* Speed (baudrate) switch */
    .speed_switcher	= superstar2_set_speed,
    /* Switch to NMEA mode */
    .mode_switcher	= superstar2_set_mode,
    /* Message delivery rate switcher (not active) */
    .rate_switcher	= NULL,
    /* Minimum cycle time (not used) */
    .min_cycle.tv_sec  = 1,		/* not relevant, no rate switch */
    .min_cycle.tv_nsec = 0,		/* not relevant, no rate switch */
#endif /* RECONFIGURE_ENABLE */
#ifdef CONTROLSEND_ENABLE
    /* Control string sender - should provide checksum and trailer */
    .control_send	= superstar2_control_send,
#endif /* CONTROLSEND_ENABLE */
    .time_offset     = NULL,		/* no method for NTP fudge factor */
};
/* *INDENT-ON* */
#endif /* defined(SUPERSTAR2_ENABLE) && defined(BINARY_ENABLE) */
