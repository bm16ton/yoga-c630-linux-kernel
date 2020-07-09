/*
 * This is the gpsd driver for GeoStar Navigation receivers
 * operating in binary mode.
 *
 * Tested with GeoS-1M GPS/GLONASS receiver.
 *
 * By Viktar Palstsiuk, viktar.palstsiuk@promwad.com
 *
 * This file is Copyright (c) 2010-2019 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 */

#include "gpsd_config.h"  /* must be before all includes */

#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "gpsd.h"
#include "bits.h"
#include "strfuncs.h"
#include "timespec.h"

#ifdef GEOSTAR_ENABLE
#define GEOSTAR_CHANNELS	24

#define JAN_2008		0x47798280 /* 1199145600 = 2008 - 1970 in seconds */

#define OFFSET(n)		((n)*4+4)

static int decode_channel_id (uint32_t ch_id) {
	int num = 0;
	num = (int)(ch_id & 0x1F);				/* SV ID */
	if((ch_id & (1<<30)) == 0) num += GLONASS_PRN_OFFSET;	/* GLONASS SV */
	else if (num == 0 ) num = 32;				/* GPS SV */
	return num;
}

static int geostar_write(struct gps_device_t *session,
			 unsigned int id, unsigned char *data, size_t len)
{
    int i;
    unsigned long cs = 0;

    putbyte(session->msgbuf, 0, 'P');
    putbyte(session->msgbuf, 1, 'S');
    putbyte(session->msgbuf, 2, 'G');
    putbyte(session->msgbuf, 3, 'G');

    putbe16(session->msgbuf, 4, id);
    putbe16(session->msgbuf, 6, len);

    /* Copy content */
    memcpy(session->msgbuf + 8, data, len * 4);

    len += 2; /* PSGG + id + len */

    /* Calculate checksum */
    for (i = 0; (size_t)i < len; i++) {
	cs ^= getleu32(session->msgbuf, i * 4);
    }

    putle32(session->msgbuf, len * 4, cs);

    len += 1; /* Checksum */

    session->msgbuflen = len * 4;

    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "Sent GeoStar packet id 0x%x\n", id);
    if (gpsd_write(session, session->msgbuf, session->msgbuflen) !=
	(ssize_t) session->msgbuflen)
	return -1;

    return 0;
}

/* geostar_detect()
 *
 * see if it looks like a GeoStar device is listening and
 * return 1 if found, 0 if not
 */
static bool geostar_detect(struct gps_device_t *session)
{
    unsigned char buf[1 * 4];
    bool ret = false;
    int myfd;

    myfd = session->gpsdata.gps_fd;

    /* request firmware revision and look for a valid response */
    putbe32(buf, 0, 0);
    if (geostar_write(session, 0xc1, buf, 1) == 0) {
	unsigned int n;
	for (n = 0; n < 3; n++) {
	    if (!nanowait(myfd, NS_IN_SEC))
		break;
	    if (generic_get(session) >= 0) {
		if (session->lexer.type == GEOSTAR_PACKET) {
		    GPSD_LOG(LOG_RAW, &session->context->errout,
			     "geostar_detect found\n");
		    ret = true;
		    break;
		}
	    }
	}
    }

    return ret;
}

static gps_mask_t geostar_analyze(struct gps_device_t *session)
{
    int i, len;
    gps_mask_t mask = 0;
    unsigned int id;
    uint16_t uw1, uw2;
    uint32_t ul1, ul2, ul3, ul4, ul5;
    double d1, d2, d3, d4, d5;
    char buf[BUFSIZ];
    char buf2[BUFSIZ];

    if (session->lexer.type != GEOSTAR_PACKET) {
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "geostar_analyze packet type %d\n",
		 session->lexer.type);
	return 0;
    }

    if (session->lexer.outbuflen < 12 || session->lexer.outbuffer[0] != 'P')
	return 0;

    /* put data part of message in buf */

    memset(buf, 0, sizeof(buf));
    /* cppcheck-suppress redundantCopy */
    memcpy(buf, session->lexer.outbuffer, session->lexer.outbuflen);

    buf2[len = 0] = '\0';
    for (i = 0; i < (int)session->lexer.outbuflen; i++) {
	str_appendf(buf2, sizeof(buf2),
		       "%02x", buf[len++] = session->lexer.outbuffer[i]);
    }

    id = (unsigned int)getleu16(session->lexer.outbuffer, OFFSET(0));

    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "GeoStar packet id 0x%02x length %d: %s\n", id, len, buf2);

    session->cycle_end_reliable = true;

    switch (id) {
    case 0x10:
	GPSD_LOG(LOG_INF, &session->context->errout, "Raw measurements\n");
	break;
    case 0x11:
	GPSD_LOG(LOG_INF, &session->context->errout, "GPS sub-frame data\n");
	break;
    case 0x12:
	GPSD_LOG(LOG_INF, &session->context->errout, "GLONASS sub-frame data\n");
	break;
    case 0x13:
	d1 = getled64(buf, OFFSET(1));
	d2 = getled64(buf, OFFSET(3));
	d3 = getled64(buf, OFFSET(5));
	d4 = getled64(buf, OFFSET(29)); /* GPS time */
	d5 = getled64(buf, OFFSET(31)); /* GLONASS time */
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "ECEF coordinates %g %g %g %f %f\n", d1, d2, d3, d4, d5);
	break;
    case 0x20:
	d1 = getled64(buf, OFFSET(1)); /* time */

        DTOTS(&session->newdata.time, d1);
        session->newdata.time.tv_sec += JAN_2008;

	session->newdata.latitude = getled64(buf, OFFSET(3)) * RAD_2_DEG;
	session->newdata.longitude = getled64(buf, OFFSET(5)) * RAD_2_DEG;
        /* altitude above ellipsoid */
	session->newdata.altHAE = getled64(buf, OFFSET(7));
	session->newdata.geoid_sep = getled64(buf, OFFSET(9));
	session->gpsdata.satellites_used = (int)getles32(buf, OFFSET(11));
	session->gpsdata.dop.gdop = getled64(buf, OFFSET(13));
	session->gpsdata.dop.pdop = getled64(buf, OFFSET(15));
	session->gpsdata.dop.tdop = getled64(buf, OFFSET(17));
	session->gpsdata.dop.hdop = getled64(buf, OFFSET(19));
	session->gpsdata.dop.vdop = getled64(buf, OFFSET(21));
	session->newdata.speed = getled64(buf, OFFSET(31));
	session->newdata.track = getled64(buf, OFFSET(33)) * RAD_2_DEG;

	ul1 = getleu32(buf, OFFSET(29)); /* status */

	if (ul1 != 0) {
	    session->gpsdata.status = STATUS_NO_FIX;
	    mask |= STATUS_SET;
	} else {
	    if (session->gpsdata.status < STATUS_FIX) {
		session->gpsdata.status = STATUS_FIX;
		mask |= STATUS_SET;
	    }
	}
	mask |= TIME_SET | NTPTIME_IS | LATLON_SET | ALTITUDE_SET |
                SPEED_SET | TRACK_SET | DOP_SET | USED_IS | REPORT_IS;

	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Geographic coordinates %f %g %g %g %g %g\n",
		 d1,
		 session->newdata.latitude,
		 session->newdata.longitude,
		 session->newdata.altHAE,
		 session->newdata.speed,
		 session->newdata.track);
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Dilution of precision %g %g %g %g %g\n",
		 session->gpsdata.dop.gdop,
		 session->gpsdata.dop.pdop,
		 session->gpsdata.dop.tdop,
		 session->gpsdata.dop.hdop,
		 session->gpsdata.dop.vdop);
	break;
    case 0x21:
	ul1 = getleu32(buf, OFFSET(1));
	ul2 = getleu32(buf, OFFSET(2));
	uw1 = getleu16(buf, OFFSET(3));
	uw2 = getleu16(buf, OFFSET(3) + 2);
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Current receiver telemetry %x %d %d %d\n",
		 ul1, ul2, uw1, uw2);
	if(ul1 & (1<<3)) {
	    session->newdata.mode = MODE_2D;
	}
	else {
	    session->newdata.mode = MODE_3D;
	}
	if(ul1 & (1<<2)) {
	    session->gpsdata.status = STATUS_FIX;
	}
	else {
	    session->gpsdata.status = STATUS_NO_FIX;
	    session->newdata.mode = MODE_NO_FIX;
	}

	mask |= MODE_SET | STATUS_SET;
	break;
    case 0x22:
	ul1 = getleu32(buf, OFFSET(1));
	GPSD_LOG(LOG_INF, &session->context->errout, "SVs in view %d\n", ul1);
	session->gpsdata.satellites_visible = (int)ul1;
	if(ul1 > GEOSTAR_CHANNELS) ul1 = GEOSTAR_CHANNELS;
	for(i = 0; (uint32_t)i < ul1; i++) {
	    int16_t s1, s2, s3;
	    ul2 = getleu32(buf, OFFSET(2) + i * 3 * 4);
	    s1 = getles16(buf, OFFSET(3) + i * 3 * 4);
	    s2 = getles16(buf, OFFSET(3) + 2 + i * 3 * 4);
	    s3 = getles16(buf, OFFSET(4) + 2 + i * 3 * 4);
	    GPSD_LOG(LOG_INF, &session->context->errout,
                     "ID %d Az %g El %g SNR %g\n",
		     decode_channel_id(ul2), s1*0.001*RAD_2_DEG,
                     s2*0.001*RAD_2_DEG, s3*0.1);
	    session->gpsdata.skyview[i].PRN = (short)decode_channel_id(ul2);
	    session->gpsdata.skyview[i].azimuth = (short)round((double)s1*0.001 * RAD_2_DEG);
	    session->gpsdata.skyview[i].elevation = (short)round((double)s2*0.001 * RAD_2_DEG);
	    session->gpsdata.skyview[i].ss = (double)s3*0.1;
	    session->gpsdata.skyview[i].used = (bool)(ul2 & (1<<27));
	}
	session->gpsdata.skyview_time.tv_sec = 0;
	session->gpsdata.skyview_time.tv_nsec = 0;
	mask |= SATELLITE_SET | USED_IS;
	break;
    case 0x3e:
	ul1 = getleu32(buf, OFFSET(1));
	ul2 = getleu32(buf, OFFSET(2));
	ul3 = getleu32(buf, OFFSET(3));
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Receiver power-up message %d %d %d\n", ul1, ul2, ul3);
	break;
    case 0x3f:
	ul1 = getleu32(buf, OFFSET(1));
	ul2 = getleu32(buf, OFFSET(2));
	GPSD_LOG(LOG_WARN, &session->context->errout,
		 "Negative acknowledge %x %d\n", ul1, ul2);
	break;
    case 0x40:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Set initial parameters\n");
	break;
    case 0x41:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Set serial ports parameters\n");
	break;
    case 0x42:
	ul1 = getleu32(buf, OFFSET(1));
	ul2 = getleu32(buf, OFFSET(2));
	ul3 = getleu32(buf, OFFSET(3));
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Set receiver operation mode %d %d %d\n",
		 ul1, ul2, ul3);
	break;
    case 0x43:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Set navigation task solution parameters\n");
	break;
    case 0x44:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Set output data rate\n");
	break;
    case 0x46:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Assign data protocol to communication port\n");
	break;
    case 0x48:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Set GPS almanac\n");
	break;
    case 0x49:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Set GLONASS almanac\n");
	break;
    case 0x4a:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Set GPS ephemeris\n");
	break;
    case 0x4b:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Set GLONASS ephemeris\n");
	break;
    case 0x4c:
	ul1 = getleu32(buf, OFFSET(1));
	ul2 = getleu32(buf, OFFSET(2));
	ul3 = getleu32(buf, OFFSET(3));
	ul4 = getleu32(buf, OFFSET(4));
	ul5 = getleu32(buf, OFFSET(5));
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Set PPS parameters %d %d %d %d %d\n",
		 ul1, ul2, ul3, ul4, ul5);
	break;
    case 0x4d:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Enable/disable SV in position fix\n");
	break;
    case 0x4e:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Enable/disable NMEA messages\n");
	break;
    case 0x4f:
	ul1 = getleu32(buf, OFFSET(1));
	ul2 = getleu32(buf, OFFSET(2));
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Enable/disable binary messages %x %x\n",
		 ul1, ul2);
	break;
    case 0x80:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Query initial parameters\n");
	break;
    case 0x81:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Query serial ports parameters\n");
	break;
    case 0x82:
	ul1 = getleu32(buf, OFFSET(1));
	ul2 = getleu32(buf, OFFSET(2));
	ul3 = getleu32(buf, OFFSET(3));
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Query receiver operation mode %d %d %d\n",
		 ul1, ul2, ul3);
	break;
    case 0x83:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Query navigation task solution parameters\n");
	break;
    case 0x84:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Query output data rate\n");
	break;
    case 0x86:
	session->driver.geostar.physical_port = (unsigned int)getleu32(buf, OFFSET(1));
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Query data protocol assignment to communication port\n");
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Connected to physical port %d\n",
		 session->driver.geostar.physical_port);
	break;
    case 0x88:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Query GPS almanac\n");
	break;
    case 0x89:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Query GLONASS almanac\n");
	break;
    case 0x8a:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Query GPS ephemerides\n");
	break;
    case 0x8b:
	d1 = getled64(buf, OFFSET(23));
	d2 = getled64(buf, OFFSET(25));
	d3 = getled64(buf, OFFSET(27));
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Query GLONASS ephemerides %g %g %g\n",
		 d1, d2, d3);
	break;
    case 0x8c:
	ul1 = getleu32(buf, OFFSET(1));
	ul2 = getleu32(buf, OFFSET(2));
	ul3 = getleu32(buf, OFFSET(3));
	ul4 = getleu32(buf, OFFSET(4));
	ul5 = getleu32(buf, OFFSET(5));
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Query PPS parameters %d %d %d %d %d\n",
		 ul1, ul2, ul3, ul4, ul5);
	break;
    case 0x8d:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Query enable/disable status of the SV in position fix\n");
	break;
    case 0x8e:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Query enable NMEA messages\n");
	break;
    case 0x8f:
	ul1 = getleu32(buf, OFFSET(1));
	ul2 = getleu32(buf, OFFSET(2));
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Query enable binary messages %x %x\n",
		 ul1, ul2);
	break;
    case 0xc0:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Change operation mode command\n");
	break;
    case 0xc1:
	ul4 = getleu32(buf, OFFSET(1));
	ul1 = getleu32(buf, OFFSET(2));
	ul2 = getleu32(buf, OFFSET(3));
	ul3 = getleu32(buf, OFFSET(4));
        (void)snprintf(session->subtype, sizeof(session->subtype),
                "%u.%u %u.%u.%u %x %c-%u\n",
                ul4>>16, ul4&0xFFFF, ul1>>9, (ul1>>5)&0xF, ul1&0x1F, ul2,
                ul3>>24, ul3&0x00FFFFFF);
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Request FW version command: %s\n",
		 session->subtype);
	mask |= DEVICEID_SET;
	break;
    case 0xc2:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Restart receiver command\n");
	break;
    case 0xc3:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Store parameters to Flash command\n");
	break;
    case 0xd0:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Erase Flash sector command\n");
	break;
    case 0xd1:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Write data to Flash command\n");
	break;
    case 0xd2:
	GPSD_LOG(LOG_INF, &session->context->errout,
		 "Response to Store Serial Number command\n");
	break;
    default:
	GPSD_LOG(LOG_WARN, &session->context->errout,
		 "Unhandled GeoStar packet type 0x%02x\n", id);
	break;
    }

    return mask;
}

static gps_mask_t geostar_parse_input(struct gps_device_t *session)
{
    if (session->lexer.type == GEOSTAR_PACKET) {
	return geostar_analyze(session);;
    } else
	return 0;
}

#ifdef CONTROLSEND_ENABLE
static ssize_t geostar_control_send(struct gps_device_t *session,
				 char *buf, size_t buflen)
/* not used by the daemon, it's for gpsctl and friends */
{
    return (ssize_t) geostar_write(session,
				(unsigned int)buf[0],
				(unsigned char *)buf + 1, (buflen - 1)/4);
}
#endif /* CONTROLSEND_ENABLE */


static void geostar_init_query(struct gps_device_t *session)
{
    unsigned char buf[2 * 4];
    /* Poll Software Version */
    (void)geostar_write(session, 0xc1, buf, 1);
}

static void geostar_event_hook(struct gps_device_t *session, event_t event)
{
    unsigned char buf[2 * 4];

    if (session->context->readonly)
	return;

    if (event == event_identified || event == event_reactivate) {
	/* Select binary packets */
	putbe32(buf, 0, 0xffff0000);
	putbe32(buf, 4, 0);
	(void)geostar_write(session, 0x4f, buf, 2);

	/* Poll Ports params */
	putbe32(buf, 0, 1);
	(void)geostar_write(session, 0x81, buf, 1);
	putbe32(buf, 0, 0);
	(void)geostar_write(session, 0x81, buf, 1);
	/* Poll Init params */
	(void)geostar_write(session, 0x80, buf, 1);
	/* Poll Mode */
	(void)geostar_write(session, 0x82, buf, 1);
	/* Poll Solution params */
	(void)geostar_write(session, 0x83, buf, 1);
	/* Poll Output rate */
	(void)geostar_write(session, 0x84, buf, 1);
	/* Poll Protocols assignment */
	(void)geostar_write(session, 0x86, buf, 1);
	/* Poll PPS params */
	(void)geostar_write(session, 0x8c, buf, 1);
	/* Poll NMEA packets selected */
	(void)geostar_write(session, 0x8e, buf, 1);
	/* Poll binary packets selected */
	(void)geostar_write(session, 0x8f, buf, 1);
    }

    if (event == event_deactivate) {
	/* Perform cold restart */
	putbe32(buf, 0, 3);
	(void)geostar_write(session, 0xc2, buf, 1);
    }
}

#ifdef RECONFIGURE_ENABLE
static bool geostar_speed_switch(struct gps_device_t *session,
			      speed_t speed, char parity, int stopbits)
{
    unsigned char buf[4 * 4];
    int iparity;

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
    iparity = parity;

    putbe32(buf, 0, session->driver.geostar.physical_port);
    putbe32(buf, 4, speed);
    putbe32(buf, 8, stopbits);
    putbe32(buf, 12, iparity);
    (void)geostar_write(session, 0x41, buf, 4);

    return true;	/* it would be nice to error-check this */
}

static void geostar_mode(struct gps_device_t *session, int mode)
{
    if (mode == MODE_NMEA) {
	unsigned char buf[1 * 4];
	/* Switch to NMEA mode */
	putbe32(buf, 0, 1);
	(void)geostar_write(session, 0x46, buf, 1);
    } else if (mode == MODE_BINARY) {
	/* Switch to binary mode */
	(void)nmea_send(session, "$GPSGG,SWPROT");
    } else {
	GPSD_LOG(LOG_ERROR, &session->context->errout,
		 "unknown mode %i requested\n", mode);
    }
}
#endif /* RECONFIGURE_ENABLE */

static double geostar_time_offset(struct gps_device_t *session UNUSED)
{
    return 0.31;
}

/* this is everything we export */
/* *INDENT-OFF* */
const struct gps_type_t driver_geostar =
{
    .type_name      = "GeoStar",	/* full name of type */
    .packet_type    = GEOSTAR_PACKET,	/* associated lexer packet type */
    .flags	    = DRIVER_STICKY,	/* remember this */
    .trigger	    = NULL,		/* no trigger */
    .channels       = GEOSTAR_CHANNELS,	/* consumer-grade GPS/GLONASS */
    .probe_detect   = geostar_detect,	/* probe for device */
    .get_packet     = generic_get,	/* use the generic packet getter */
    .parse_packet   = geostar_parse_input,	/* parse message packets */
    .rtcm_writer    = NULL,		/* doesn't accept DGPS corrections */
    .init_query     = geostar_init_query,	/* non-perturbing initial query */
    .event_hook     = geostar_event_hook,	/* fire on various lifetime events */
#ifdef RECONFIGURE_ENABLE
    .speed_switcher = geostar_speed_switch,/* change baud rate */
    .mode_switcher  = geostar_mode,	/* there is a mode switcher */
    .rate_switcher  = NULL,		/* no rate switcher */
    .min_cycle.tv_sec  = 1,		/* not relevant, no rate switch */
    .min_cycle.tv_nsec = 0,		/* not relevant, no rate switch */
#endif /* RECONFIGURE_ENABLE */
#ifdef CONTROLSEND_ENABLE
    .control_send   = geostar_control_send,/* how to send commands */
#endif /* CONTROLSEND_ENABLE */
    .time_offset     = geostar_time_offset,
};
/* *INDENT-ON* */

#endif /* GEOSTAR_ENABLE */
