/*
 * Driver for Navcom receivers using proprietary NCT messages, a binary protocol.
 *
 * Vendor website: http://www.navcomtech.com/
 * Technical references: Technical Reference Manual P/N 96-3120001-3001
 *
 * Tested with two SF-2040G models
 *
 * At this stage, this driver implements the following commands:
 *
 * 0x20: Data Request (tell the unit which responses you want)
 * 0x3f: LED Configuration (controls the front panel LEDs -- for testing)
 * 0x1c: Test Support Block (again, blinks the front panel lights)
 *
 * and it understands the following responses:
 *
 * 0x06: Acknowledgement (without error)
 * 0x15: Negative Acknowledge
 * 0x86: Channel Status
 * 0xae: Identification Block
 * 0xb0: Raw Meas. Data Block
 * 0xb1: PVT Block
 * 0xb5: Pseudorange Noise Statistics
 * 0xd3: LBM DSP Status Block
 * 0xef: Clock Drift and Offset
 *
 * By Diego Berge. Contact via web form at http://www.navlost.eu/contact
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
#include "gpsd.h"

#if defined(NAVCOM_ENABLE)
#include "bits.h"
#include "timespec.h"

/* Have data which is 24 bits long */
#define getles3224(buf,off)  (int32_t)(((uint32_t)getub((buf), (off)+2)<<24 | (uint32_t)getub((buf), (off)+1)<<16 | (uint32_t)getub((buf), (off))<<8)>>8)
#define getleu3224(buf,off) (uint32_t)(((uint32_t)getub((buf), (off)+2)<<24 | (uint32_t)getub((buf), (off)+1)<<16 | (uint32_t)getub((buf), (off))<<8)>>8)

/* And just to be difficult, Navcom is little endian but the GPS data stream
   is big endian.  Some messages contain raw GPS data */
#define getles16_be(buf, off)	(int16_t)((((uint16_t)getub(buf, (off)) << 8) \
				    | (uint16_t)getub(buf, (off)+1)))
#define getleu16_be(buf, off)	(uint16_t)((((uint16_t)getub(buf, (off)) << 8) \
				    | (uint16_t)getub(buf, (off)+1)))
#define getles32_be(buf, off)	(int32_t)((((uint16_t)getleu16_be(buf, (off)) << 16) \
				    | getleu16_be(buf, (off)+2)))
#define getleu32_be(buf, off)	(uint32_t)((((uint16_t)getleu16_be(buf, (off)) << 16) \
				    | getleu16_be(buf, (off)+2)))
#define getles64_be(buf, off)	(int64_t)((((uint64_t)getleu32_be(buf, (off)) << 32) \
				    | getleu32_be(buf, (off)+4)))
#define getleu64_be(buf, off)	(uint64_t)((((uint64_t)getleu32_be(buf, (off)) << 32) \
				    | getleu32_be(buf, (off)+4)))
#define getles3224_be(buf,off)     (int32_t)(((uint32_t)getub((buf), (off))<<24 \
				    | (uint32_t)getub((buf), (off)+1)<<16 \
				    | (uint32_t)getub((buf), (off)+2)<<8)>>8)

#define NAVCOM_CHANNELS	12

static uint8_t checksum(unsigned char *buf, size_t len)
{
    size_t n;
    uint8_t csum = (uint8_t) 0x00;
    for (n = 0; n < len; n++)
	csum ^= buf[n];
    return csum;
}

static bool navcom_send_cmd(struct gps_device_t *session, unsigned char *cmd,
			    size_t len)
{
    return (gpsd_write(session, (const char *)cmd, len) == (ssize_t) len);
}

/* Data Request */
static void navcom_cmd_0x20(struct gps_device_t *session, uint8_t block_id,
			    uint16_t rate)
{
    unsigned char msg[18];
    putbyte(msg, 0, 0x02);
    putbyte(msg, 1, 0x99);
    putbyte(msg, 2, 0x66);
    putbyte(msg, 3, 0x20);	/* Cmd ID */
    putle16(msg, 4, 0x000e);	/* Length */
    putbyte(msg, 6, 0x00);	/* Action */
    putbyte(msg, 7, 0x01);	/* Count of blocks */
    putbyte(msg, 8, block_id);	/* Data Block ID */
    putbyte(msg, 9, 0x02);	/* Logical Ports */
    putle16(msg, 10, rate);	/* Data rate */
    putbyte(msg, 12, 0x71);
    putbyte(msg, 13, 0x00);
    putle16(msg, 14, 0x0000);
    putbyte(msg, 16, checksum(msg + 3, 13));
    putbyte(msg, 17, 0x03);
    (void)navcom_send_cmd(session, msg, 18);
    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "Navcom: sent command 0x20 (Data Request) "
	     "- data block id = %02x at rate %02x\n", block_id, rate);
}

// cppcheck-suppress unusedFunction
static void UNUSED navcom_cmd_0x3f(struct gps_device_t *session)
/* Changes the LED settings in the receiver */
{
    unsigned char msg[12];
    putbyte(msg, 0, 0x02);
    putbyte(msg, 1, 0x99);
    putbyte(msg, 2, 0x66);
    putbyte(msg, 3, 0x3f);	/* Cmd ID */
    putle16(msg, 4, 0x0008);
    putbyte(msg, 6, 0x01);	/* Action */
    putbyte(msg, 7, 0x00);	/* Reserved */
    putbyte(msg, 8, 0x02);	/* Link LED setting */
    putbyte(msg, 9, 0x0a);	/* Battery LED setting */
    putbyte(msg, 10, checksum(msg + 3, 7));
    putbyte(msg, 11, 0x03);
    (void)navcom_send_cmd(session, msg, 12);
    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "Navcom: sent command 0x3f (LED Configuration Block)\n");
}

/* Test Support Block - Blinks the LEDs */
static void navcom_cmd_0x1c(struct gps_device_t *session, uint8_t mode,
			    uint8_t length)
{
    unsigned char msg[12];
    putbyte(msg, 0, 0x02);
    putbyte(msg, 1, 0x99);
    putbyte(msg, 2, 0x66);
    putbyte(msg, 3, 0x1c);	/* Cmd ID */
    putle16(msg, 4, 0x0008);
    putbyte(msg, 6, 0x04);	/* Use ACK/NAK */
    putbyte(msg, 7, mode);	/* 0x01 or 0x02 */
    putbyte(msg, 8, length);	/* Only if mode == 0x01 */
    putbyte(msg, 9, 0x00);
    putbyte(msg, 10, checksum(msg + 3, 7));
    putbyte(msg, 11, 0x03);
    (void)navcom_send_cmd(session, msg, 12);
    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "Navcom: sent command 0x1c (Test Support Block)\n");
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: command 0x1c mode = %02x, length = %u\n",
	     mode, length);
}

#ifdef RECONFIGURE_ENABLE
/* Serial Port Configuration */
static void navcom_cmd_0x11(struct gps_device_t *session,
			    uint8_t port_selection)
{
    /* NOTE - We only allow changing one port at a time,
     * although the message supports doing both at once. */
    unsigned char msg[12];
    putbyte(msg, 0, 0x02);
    putbyte(msg, 1, 0x99);
    putbyte(msg, 2, 0x66);
    putbyte(msg, 3, 0x11);	/* Cmd ID */
    putle16(msg, 4, 0x0008);	/* Length */
    putbyte(msg, 6, 0x04);	/* Action - Use ACK/NAK) */
    putbyte(msg, 7, port_selection);
    putbyte(msg, 8, 0x00);	/* Reserved */
    putbyte(msg, 9, 0x00);	/* Reserved */
    putbyte(msg, 10, checksum(msg + 3, 7));
    putbyte(msg, 11, 0x03);
    (void)navcom_send_cmd(session, msg, 12);
    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "Navcom: sent command 0x11 (Serial Port Configuration)\n");
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: serial port selection: 0x%02x\n", port_selection);
}
#endif /* RECONFIGURE_ENABLE */

static void navcom_event_hook(struct gps_device_t *session, event_t event)
{
    if (session->context->readonly)
	return;

    /* Request the following messages: */
    if (event == event_identified) {
	/* NOTE - Channel Status allows us to know into which of the
	 * unit's various serial ports we are connected.
	 * Its value gets updated every time we receive a 0x06 (Ack)
	 * message.  Note that if commands are being fed into the
	 * unit from more than one port (which is entirely possible
	 * although not necessarily a bright idea), there is a good
	 * chance that we might misidentify our port */
	navcom_cmd_0x1c(session, 0x02, 0);	/* Test Support Block */
	navcom_cmd_0x20(session, 0xae, 0x0000);	/* Identification Block */
	navcom_cmd_0x20(session, 0x86, 0x000a);	/* Channel Status */
	navcom_cmd_0x1c(session, 0x01, 5);	/* Blink LEDs on receiver */
	navcom_cmd_0x20(session, 0xae, 0x1770);	/* Identification Block - send every 10 min */
	navcom_cmd_0x20(session, 0xb1, 0x4000);	/* PVT Block */
	navcom_cmd_0x20(session, 0xb5, 0x00c8);	/* Pseudorange Noise Statistics - send every 20s */
	navcom_cmd_0x20(session, 0xb0, 0x4000);	/* Raw Meas Data Block */
	navcom_cmd_0x20(session, 0x81, 0x0000);	/* Packed Ephemeris Data - send once */
	navcom_cmd_0x20(session, 0x81, 0x4000);	/* Packed Ephemeris Data */
	navcom_cmd_0x20(session, 0x86, 0x4000);	/* Channel Status */
	navcom_cmd_0x20(session, 0x83, 0x4000);	/* Ionosphere and UTC Data */
	navcom_cmd_0x20(session, 0xef, 0x0bb8);	/* Clock Drift - send every 5 min */
    }
}

/* Ionosphere and UTC Data */
static gps_mask_t handle_0x83(struct gps_device_t *session)
{
    /* NOTE - At the present moment this is only being used
     * for determining the GPS-UTC time difference,
     * for which the iono data is not needed as far
     * as we are concerned.  However, I am still
     * reporting it (if debuglevel >= LOG_DATA) as a
     * matter of interest */
/* 2^-30 */
#define SF_A0 (0.000000000931322574615478515625)
/* 2^-50 */
#define SF_A1 (0.000000000000000888178419700125)
/* 2^12 */
#define SF_TOT (4096)
/* 2^-30 */
#define SF_ALPHA0 (0.000000000931322574615478515625)
/* 2^-27 */
#define SF_ALPHA1 (0.000000007450580596923828125)
/* 2^-24 */
#define SF_ALPHA2 (0.000000059604644775390625)
/* 2^-24 */
#define SF_ALPHA3 (0.000000059604644775390625)
/* 2^11 */
#define SF_BETA0 (2048)
/* 2^14 */
#define SF_BETA1 (16384)
/* 2^16 */
#define SF_BETA2 (65536)
/* 2^16 */
#define SF_BETA3 (65536)
    unsigned char *buf = session->lexer.outbuffer + 3;
    uint16_t week = getleu16(buf, 3);
    uint32_t tow = getleu32(buf, 5);
    int8_t alpha0 = getsb(buf, 9);
    int8_t alpha1 = getsb(buf, 10);
    int8_t alpha2 = getsb(buf, 11);
    int8_t alpha3 = getsb(buf, 12);
    int8_t beta0 = getsb(buf, 13);
    int8_t beta1 = getsb(buf, 14);
    int8_t beta2 = getsb(buf, 15);
    int8_t beta3 = getsb(buf, 16);
    int32_t a1 = getles32(buf, 17);
    int32_t a0 = getles32(buf, 21);
    uint8_t tot = getub(buf, 25);
    uint8_t wnt = getub(buf, 26);
    int8_t dtls = getsb(buf, 27);
    uint8_t wnlsf = getub(buf, 28);
    uint8_t dn = getub(buf, 29);
    int8_t dtlsf = getsb(buf, 30);

    /* Ref.: ICD-GPS-200C 20.3.3.5.2.4 */
    if ((week % 256) * 604800 + tow / 1000.0 < wnlsf * 604800 + dn * 86400) {
	/* Effectivity time is in the future, use dtls */
	session->context->leap_seconds = (int)dtls;
    } else {
	/* Effectivity time is not in the future, use dtlsf */
	session->context->leap_seconds = (int)dtlsf;
    }

    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "Navcom: received packet type 0x83 (Ionosphere and UTC Data)\n");
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: Scaled parameters follow:\n");
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: GPS Week: %u, GPS Time of Week: %u (GPS Time: %f)\n",
	     week, tow, week * 604800 + tow / 1000.0);
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: a0: %12.4E, a1: %12.4E, a2: %12.4E, a3: %12.4E, "
	     "b0: %12.4E, b1: %12.4E, b2: %12.4E, b3: %12.4E\n",
	     (double)alpha0 * SF_ALPHA0, (double)alpha1 * SF_ALPHA1,
	     (double)alpha2 * SF_ALPHA2, (double)alpha3 * SF_ALPHA3,
	     (double)beta0 * SF_BETA0, (double)beta1 * SF_BETA1,
	     (double)beta2 * SF_BETA2, (double)beta3 * SF_BETA3);
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: A0: %19.12E, A1: %19.12E\n", (double)a0 * SF_A0,
	     (double)a1 * SF_A1);
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: UTC Ref. Time: %lu, UTC Ref. Week: %u, dTls: %d\n",
	     (unsigned long)tot * SF_TOT, wnt, dtls);
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: Week of leap seconds: %u, Day number of leap seconds: %u, dTlsf: %d\n",
	     wnlsf, dn, dtlsf);

    return 0;			/* No flag for update of leap seconds (Not part of a fix) */

#undef SF_A0
#undef SF_A1
#undef SF_TOT
#undef SF_ALPHA0
#undef SF_ALPHA1
#undef SF_ALPHA2
#undef SF_ALPHA3
#undef SF_BETA0
#undef SF_BETA1
#undef SF_BETA2
#undef SF_BETA3
}

/* Acknowledgement (without error) */
static gps_mask_t handle_0x06(struct gps_device_t *session)
{
    unsigned char *buf = session->lexer.outbuffer + 3;
    uint8_t cmd_id = getub(buf, 3);
    uint8_t port = getub(buf, 4);
    session->driver.navcom.physical_port = port;	/* This tells us which serial port was used last */
    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "Navcom: received packet type 0x06 (Acknowledgement (without error))\n");
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: acknowledged command id 0x%02x on port %c\n",
	     cmd_id, (port == 0 ? 'A' : (port == 1 ? 'B' : '?')));
    return 0;			/* Nothing updated */
}

/* Negative Acknowledge */
static gps_mask_t handle_0x15(struct gps_device_t *session)
{
    size_t n;
    unsigned char *buf = session->lexer.outbuffer + 3;
    size_t msg_len = (size_t) getleu16(buf, 1);
    uint8_t port, cmd_id = getub(buf, 3);
    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "Navcom: received packet type 0x15 (Negative Acknowledge)\n");
    /* coverity_submit[tainted_data] */
    for (n = 4; n < (msg_len - 2); n += 2) {
	uint8_t err_id = getub(buf, n);
	uint8_t err_desc = getub(buf, n + 1);
	GPSD_LOG(LOG_DATA, &session->context->errout,
		 "Navcom: error id = 0x%02x, error description = 0x%02x\n",
		 err_id, err_desc);
    }
    port = getub(buf, n);
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: negative acknowledge was for command id 0x%02x on port %c\n",
	     cmd_id, (port == 0 ? 'A' : (port == 1 ? 'B' : '?')));
    return 0;			/* Nothing updated */
}

/* PVT Block */
static gps_mask_t handle_0xb1(struct gps_device_t *session)
{
    gps_mask_t mask;
    unsigned char *buf = session->lexer.outbuffer + 3;
    uint16_t week;
    uint32_t tow;
    timespec_t ts_tow;
    int32_t lat, lon;
    char ts_buf[TIMESPEC_LEN];
    /* Resolution of lat/lon values (2^-11) */
#define LL_RES (0.00048828125)
    uint8_t lat_fraction, lon_fraction;
    /* Resolution of lat/lon fractions (2^-15) */
#define LL_FRAC_RES (0.000030517578125)
    uint8_t nav_mode;
    int32_t ellips_height, altitude;
    /* Resolution of height and altitude values (2.0^-10) */
#define EL_RES (0.0009765625)
    double vel_north, vel_east, vel_up;
    uint8_t gdop, pdop, hdop, vdop, tdop;
    /* This value means "undefined" */
#define DOP_UNDEFINED (255)

    int16_t ant_height_adj;
    int32_t set_delta_up;
    /* Resolution of delta north, east, and up,
     * and ant. height adjustment values (1mm) */
#define D_RES (0.001)

#ifdef __UNUSED__
    /* Other values provided by the PVT block which we
     * may want to provide in the future.
     */
    uint8_t dgps_conf;
    uint16_t max_dgps_age;
    uint8_t ext_nav_mode;
    int32_t set_delta_north, set_delta_east;
    uint8_t nav_failure_code;
#endif /* __UNUSED__ */

    /* Timestamp */
    week = (uint16_t) getleu16(buf, 3);
    tow = (uint32_t) getleu32(buf, 5);        /* tow in ms */
    MSTOTS(&ts_tow, tow);
    session->newdata.time = gpsd_gpstime_resolv(session, week, ts_tow);

    /* Get latitude, longitude */
    lat = getles32(buf, 13);
    lon = getles32(buf, 17);
    lat_fraction = (uint8_t) (getub(buf, 21) >> 4);
    lon_fraction = (uint8_t) (getub(buf, 21) & 0x0f);

    session->newdata.latitude =
	(double)(lat * LL_RES + lat_fraction * LL_FRAC_RES) / 3600;
    session->newdata.longitude =
	(double)(lon * LL_RES + lon_fraction * LL_FRAC_RES) / 3600;

    /* Nav mode */
    nav_mode = (uint8_t) getub(buf, 22);
    if (-nav_mode & 0x80) {
	session->gpsdata.status = STATUS_NO_FIX;
	session->newdata.mode = MODE_NO_FIX;
    } else {
	session->newdata.mode = ((nav_mode & 0x40)!=0 ? MODE_3D : MODE_2D);
	session->gpsdata.status =
	    ((nav_mode & 0x03)!=0 ? STATUS_DGPS_FIX : STATUS_FIX);
    }

    /* altHAE */
    ellips_height = getles32(buf, 23);
    /* altMSL */
    altitude = getles32(buf, 27);

    ant_height_adj = getles16(buf, 51);
    set_delta_up = getles32(buf, 79);

    session->newdata.altMSL = (double)(altitude * EL_RES)
	+ (ant_height_adj * D_RES) + (set_delta_up * D_RES);
    session->newdata.altHAE = (double)(ellips_height) * EL_RES
	+ (ant_height_adj * D_RES) + (set_delta_up * D_RES);
    /* Let gpsd_error_model() deal with geoid_sep */

    /* Speed Data */
    vel_north = (double)getles3224(buf, 31);
    vel_east = (double)getles3224(buf, 34);
    vel_up = (double)getles3224(buf, 37);

    session->newdata.NED.velN = vel_north * 0.1;
    session->newdata.NED.velE = vel_east * 0.1;
    session->newdata.NED.velD = -vel_up * 0.1;

    /* Quality indicators */
    /* UNUSED fom = getub(buf, 40);     * FOM is DRMS */
    gdop = getub(buf, 41);
    pdop = getub(buf, 42);
    hdop = getub(buf, 43);
    vdop = getub(buf, 44);
    tdop = getub(buf, 45);
    /* UNUSED tfom = getub(buf, 46);    * tfom == 10 * TDOP */

    /* let gpsd_error_model() do the error estimates */

    if (gdop != DOP_UNDEFINED)
	session->gpsdata.dop.gdop = gdop / 10.0;
    if (pdop != DOP_UNDEFINED)
	session->gpsdata.dop.pdop = pdop / 10.0;
    if (hdop != DOP_UNDEFINED)
	session->gpsdata.dop.hdop = hdop / 10.0;
    if (vdop != DOP_UNDEFINED)
	session->gpsdata.dop.vdop = vdop / 10.0;
    if (tdop != DOP_UNDEFINED)
	session->gpsdata.dop.tdop = tdop / 10.0;

    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "Navcom: received packet type 0xb1 (PVT Report)\n");
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: navigation mode %s (0x%02x) - %s - %s\n",
	     ((-nav_mode & 0x80)!='\0' ? "invalid" : "valid"), nav_mode,
	     ((nav_mode & 0x40)!='\0' ? "3D" : "2D"),
	     ((nav_mode & 0x03)!='\0' ? "DGPS" : "GPS"));
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: velocities: north = %f east = %f up = %f\n",
	     session->newdata.NED.velN,
	     session->newdata.NED.velE,
	     -session->newdata.NED.velD);
#undef D_RES
#undef LL_RES
#undef LL_FRAC_RES
#undef EL_RES
#undef VEL_RES
#undef DOP_UNDEFINED

    mask = LATLON_SET | ALTITUDE_SET | STATUS_SET | MODE_SET | USED_IS |
           HERR_SET | TIMERR_SET | DOP_SET | VNED_SET | TIME_SET | NTPTIME_IS;
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "PVT 0xb1: time=%s, lat=%.2f lon=%.2f altHAE=%.2f "
             "altMSL %.2f mode=%d status=%d gdop=%.2f pdop=%.2f hdop=%.2f "
             "vdop=%.2f tdop=%.2f mask={%s}\n",
             timespec_str(&session->newdata.time, ts_buf, sizeof(ts_buf)),
	     session->newdata.latitude,
	     session->newdata.longitude,
	     session->newdata.altHAE,
	     session->newdata.altMSL,
	     session->newdata.mode,
	     session->gpsdata.status,
	     session->gpsdata.dop.gdop,
	     session->gpsdata.dop.pdop,
	     session->gpsdata.dop.hdop,
	     session->gpsdata.dop.vdop, session->gpsdata.dop.tdop,
             gps_maskdump(mask));
    return mask;
}

/* Packed Ephemeris Data */
static gps_mask_t handle_0x81(struct gps_device_t *session)
{
    /* Scale factors for everything */
    /* 2^-31 */
#define SF_TGD       (.000000000465661287307739257812)
    /* 2^4 */
#define SF_TOC     (16)
    /* 2^-55 */
#define SF_AF2       (.000000000000000027755575615628)
    /* 2^-43 */
#define SF_AF1       (.000000000000113686837721616029)
    /* 2^-31 */
#define SF_AF0       (.000000000465661287307739257812)
    /* 2^-5 */
#define SF_CRS       (.031250000000000000000000000000)
    /* 2^-43 */
#define SF_DELTA_N   (.000000000000113686837721616029)
    /* 2^-31 */
#define SF_M0	(.000000000465661287307739257812)
    /* 2^-29 */
#define SF_CUC       (.000000001862645149230957031250)
    /* 2^-33 */
#define SF_E	 (.000000000116415321826934814453)
    /* 2^-29 */
#define SF_CUS       (.000000001862645149230957031250)
    /* 2^-19 */
#define SF_SQRT_A    (.000001907348632812500000000000)
    /* 2^4 */
#define SF_TOE     (16)
    /* 2^-29 */
#define SF_CIC       (.000000001862645149230957031250)
    /* 2^-31 */
#define SF_OMEGA0    (.000000000465661287307739257812)
    /* 2^-29 */
#define SF_CIS       (.000000001862645149230957031250)
    /* 2^-31 */
#define SF_I0	(.000000000465661287307739257812)
    /* 2^-5 */
#define SF_CRC       (.031250000000000000000000000000)
    /* 2^-31 */
#define SF_OMEGA     (.000000000465661287307739257812)
    /* 2^-43 */
#define SF_OMEGADOT  (.000000000000113686837721616029)
    /* 2^-43 */
#define SF_IDOT      (.000000000000113686837721616029)

    char ts_buf[TIMESPEC_LEN];
    unsigned char *buf = session->lexer.outbuffer + 3;
    uint8_t prn = getub(buf, 3);
    uint16_t week = getleu16(buf, 4);
    uint32_t tow = getleu32(buf, 6);
    uint16_t iodc = getleu16(buf, 10);
    /* And now the fun starts... everything that follows is
     * raw GPS data minus parity */
    /* Subframe 1, words 3 to 10 minus parity */
    uint16_t wn = (getleu16_be(buf, 12) & 0xffc0) >> 6;
    uint8_t cl2 = (getub(buf, 13) & 0x30) >> 4;
    uint8_t ura = getub(buf, 13) & 0x0f;
    uint8_t svh = (getub(buf, 14) & 0xfc) >> 2;
    /* We already have IODC from earlier in the message, so
     * we do not decode again */
/*    uint16_t iodc = (getub(buf, 14)&0x03)<<8;*/
    uint8_t l2pd = (getub(buf, 15) & 0x80) >> 7;
    int8_t tgd = getsb(buf, 26);
/*    iodc |= getub(buf, 27);*/
    uint16_t toc = getleu16_be(buf, 28);
    int8_t af2 = getsb(buf, 30);
    int16_t af1 = getles16_be(buf, 31);
    int32_t af0 = getles3224_be(buf, 33) >> 2;
    /* Subframe 2, words 3 to 10 minus parity */
    uint8_t iode = getub(buf, 36);
    int16_t crs = getles16_be(buf, 37);
    int16_t delta_n = getles16_be(buf, 39);
    int32_t m0 = getles32_be(buf, 41);
    int16_t cuc = getles16_be(buf, 45);
    uint32_t e = getleu32_be(buf, 47);
    int16_t cus = getles16_be(buf, 51);
    uint32_t sqrt_a = getleu32_be(buf, 53);
    uint16_t toe = getleu16_be(buf, 57);
    /* NOTE - Fit interval & AODO not collected */
    /* Subframe 3, words 3 to 10 minus parity */
    int16_t cic = getles16_be(buf, 60);
    int32_t Omega0 = getles32_be(buf, 62);
    int16_t cis = getles16_be(buf, 66);
    int32_t i0 = getles32_be(buf, 68);
    int16_t crc = getles16_be(buf, 72);
    int32_t omega = getles32_be(buf, 74);
    int32_t Omegadot = getles3224_be(buf, 78);
    /* Question: What is the proper way of shifting a signed int 2 bits to
     * the right, preserving sign? Answer: integer division by 4. */
    int16_t idot = (int16_t) (((getles16_be(buf, 82) & 0xfffc) / 4) |
                              ((getub(buf, 82) & 80) ? 0xc000 : 0x0000));
    session->context->gps_week = (unsigned short)wn;
    DTOTS(&session->context->gps_tow, (double)(toc * SF_TOC));
    /* leap second? */
    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "Navcom: received packet type 0x81 (Packed Ephemeris Data)\n");
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: PRN: %u, Week: %u, TOW: %s "
             "SV clock bias/drift/drift rate: %#19.12E/%#19.12E/%#19.12E\n",
	     prn,
	     session->context->gps_week,
             timespec_str(&session->context->gps_tow, ts_buf, sizeof(ts_buf)),
	     ((double)af0) * SF_AF0,
	     ((double)af1) * SF_AF1, ((double)af2) * SF_AF2);
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: IODE (!AODE): %u Crs: %19.12e, Delta n: %19.12e, M0: %19.12e\n",
	     iode, (double)crs * SF_CRS,
	     (double)delta_n * SF_DELTA_N * GPS_PI,
	     (double)m0 * SF_M0 * GPS_PI);
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: Cuc: %19.12e, Eccentricity: %19.12e, Cus: %19.12e, A^1/2: %19.12e\n",
	     (double)cuc * SF_CUC, (double)e * SF_E, (double)cus * SF_CUS,
	     (double)sqrt_a * SF_SQRT_A);
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: TOE: %u, Cic: %19.12e, Omega %19.12e, Cis: %19.12e\n",
	     toe * SF_TOE, (double)cic * SF_CIC,
	     (double)Omega0 * SF_OMEGA0 * GPS_PI, (double)cis * SF_CIS);
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: i0: %19.12e, Crc: %19.12e, omega: %19.12e, Omega dot: %19.12e\n",
	     (double)i0 * SF_I0 * GPS_PI, (double)crc * SF_CRC,
	     (double)omega * SF_OMEGA * GPS_PI,
	     (double)Omegadot * SF_OMEGADOT * GPS_PI);
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: IDOT: %19.12e, Codes on L2: 0x%x, GPS Week: %u, L2 P data flag: %x\n",
	     (double)idot * SF_IDOT * GPS_PI, cl2,
	     week - (week % 1024) + wn, l2pd);
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: SV accuracy: 0x%x, SV health: 0x%x, TGD: %f, IODC (!AODC): %u\n",
	     ura, svh, (double)tgd * SF_TGD, iodc);
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: Transmission time: %u\n", tow);

#undef SF_TGD
#undef SF_TOC
#undef SF_AF2
#undef SF_AF1
#undef SF_AF0
#undef SF_CRS
#undef SF_DELTA_N
#undef SF_M0
#undef SF_CUC
#undef SF_E
#undef SF_CUS
#undef SF_SQRT_A
#undef SF_TOE
#undef SF_CIC
#undef SF_OMEGA0
#undef SF_CIS
#undef SF_I0
#undef SF_CRC
#undef SF_OMEGA
#undef SF_OMEGADOT
#undef SF_IDOT

    return 0;
}

/* Channel Status */
static gps_mask_t handle_0x86(struct gps_device_t *session)
{
    size_t n, i, nsu;
    unsigned char *buf = session->lexer.outbuffer + 3;
    size_t msg_len = (size_t) getleu16(buf, 1);
    uint16_t week = getleu16(buf, 3);
    uint32_t tow = getleu32(buf, 5);
    uint8_t eng_status = getub(buf, 9);
    uint16_t sol_status = getleu16(buf, 10);
    uint8_t sats_visible = getub(buf, 12);
    //uint8_t sats_tracked = getub(buf, 13);
    //uint8_t used_sats = getub(buf, 14);
    //uint8_t pdop = getub(buf, 15);
    timespec_t ts_tow;

    MSTOTS(&ts_tow, tow);

    /* Timestamp */
    session->gpsdata.skyview_time = gpsd_gpstime_resolv(session,
						      (unsigned short)week,
						      ts_tow);

    /* Give this driver a single point of truth about DOPs */
    //session->gpsdata.dop.pdop = (int)pdop / 10.0;

    /* Satellite count */
    session->gpsdata.satellites_visible = (int)sats_visible;

    /* Fix mode */
    switch (sol_status & 0x05) {
    case 0x05:
	session->gpsdata.status = STATUS_DGPS_FIX;
	break;
    case 0x01:
	session->gpsdata.status = STATUS_FIX;
	break;
    default:
	session->gpsdata.status = STATUS_NO_FIX;
    }

    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: engine status 0x%x almanac %s time 0x%x pos 0x%x\n",
	     eng_status & 0x07, ((eng_status & 0x08) ? "valid" : "invalid"),
	     eng_status & 0x30 >> 4, eng_status & 0xc0 >> 6);

    /* Satellite details */
    i = nsu = 0;
    /* coverity_submit[tainted_data] */
    for (n = 17; n < msg_len; n += 14) {
	uint8_t prn, ele, ca_snr, p2_snr, log_channel, hw_channel, s, stat;
	uint16_t azm, dgps_age;
	if (i >= MAXCHANNELS) {
	    GPSD_LOG(LOG_ERROR, &session->context->errout,
		     "Navcom: packet type 0x86: too many satellites!\n");
	    gpsd_zero_satellites(&session->gpsdata);
	    return 0;
	}
	prn = getub(buf, n);
	/*
	 * This field is described in the Technical Reference as follows:
	 *
	 * Channel Tracking Status:
	 * B0-B1: C/A tracking status
	 * B2-B3: P1 tracking status
	 * B4-B5: P2 tracking status
	 *    00 Acquisition or reacquisition
	 *    01 Code loop locked
	 *    02 Costas loop locked
	 *    11 Full tracking with aiding and active
	 *       multipath reduction - all data is valid
	 * B6=1: C/A Bit sync
	 * B7=1: C/A Frame sync
	 *
	 * By observation, the satellite is in use if this status is 0xff.
	 * But errors here are not very serious, all they can affect is
	 * the coverance-matrix calculation for error modeling.
	 */
	stat = getub(buf, n + 1);
	log_channel = getub(buf, n + 2);
	ele = getub(buf, n + 5);
	azm = getleu16(buf, n + 6);
	ca_snr = getub(buf, n + 8);
	p2_snr = getub(buf, n + 10);
	dgps_age = getleu16(buf, n + 11);
	hw_channel = getub(buf, n + 13);
	s = (unsigned char)0;
	/* NOTE - In theory, I think one would check for hw channel number to
	 * see if one is dealing with a GPS or other satellite, but the
	 * channel numbers reported bear no resemblance to what the spec
	 * says should be.  So I check for the fact that if all three
	 * values below are zero, one is not interested in this satellite */
	if (!(ele == 0 && azm == 0 && dgps_age == 0)) {
	    session->gpsdata.skyview[i].PRN = (short)prn;
	    session->gpsdata.skyview[i].elevation = (double)ele;
	    session->gpsdata.skyview[i].azimuth = (double)azm;
	    s = session->gpsdata.skyview[i].ss =
                (p2_snr ? p2_snr : ca_snr) / 4.0;
	    session->gpsdata.skyview[i++].used = (stat == 0xff);
	    if (stat == 0xff)
		nsu++;
	}
	session->gpsdata.satellites_used = (int)nsu;
	GPSD_LOG(LOG_DATA, &session->context->errout,
		 "Navcom: prn = %3u, ele = %02u, azm = %03u, snr = %d (%s), "
		 "dgps age = %.1fs, log ch = %d, hw ch = 0x%02x\n",
		 prn, ele, azm, s, (p2_snr ? "P2" : "C/A"),
		 (double)dgps_age * 0.1, log_channel & 0x3f, hw_channel);
	GPSD_LOG(LOG_DATA, &session->context->errout,
		 "Navcom:	    sol. valid = %c, clock = %s, pos. = %s, "
		 "height = %s, err. code = 0x%x\n",
		 ((sol_status & 0x01) ? 'Y' : 'N'),
		 ((sol_status & 0x02) ? "stable" : "unstable"),
		 ((sol_status & 0x04) ? "dgps" : "unaided"),
		 ((sol_status & 0x08) ? "solved" : "constrained"),
		 ((sol_status & 0x01) ? 0x00 : sol_status & 0x0f00 >> 8));
    }

    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "CS 0x86: visible=%d, used=%d, mask={SATELLITE|STATUS}\n",
	     session->gpsdata.satellites_visible,
	     session->gpsdata.satellites_used);
    return SATELLITE_SET | STATUS_SET;
}

/* Raw Meas. Data Block */
static gps_mask_t handle_0xb0(struct gps_device_t *session)
{
    char ts_buf[TIMESPEC_LEN];
    /* L1 wavelength (299792458m/s / 1575420000Hz) */
#define LAMBDA_L1 (.190293672798364880476317426464)
    size_t n;
    unsigned char *buf = session->lexer.outbuffer + 3;
    size_t msg_len = (size_t) getleu16(buf, 1);
    uint16_t week = getleu16(buf, 3);
    uint32_t tow = getleu32(buf, 5);
    uint8_t tm_slew_acc = getub(buf, 9);
    uint8_t status = getub(buf, 10);

    session->context->gps_week = (unsigned short)week;
    MSTOTS(&session->context->gps_tow, tow);

    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "Navcom: received packet type 0xb0 (Raw Meas. Data Block)\n");
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: week = %u, tow = %s "
             "time slew accumulator = %u (1/1023mS), status = 0x%02x "
	     "(%sclock %s - %u blocks follow)\n",
	     session->context->gps_week,
             timespec_str(&session->context->gps_tow, ts_buf, sizeof(ts_buf)),
	     tm_slew_acc, status,
	     ((status & 0x80) ? "channel time set - " : ""),
	     ((status & 0x40) ? "stable" : "not stable"), status & 0x0f);
    /* coverity_submit[tainted_data] */
    for (n = 11; n < msg_len - 1; n += 16) {
	uint8_t sv_status = getub(buf, n);
	uint8_t ch_status = getub(buf, n + 1);
	uint32_t ca_pseudorange = getleu32(buf, n + 2);
	/* integer division by 16 is a sign-preserving right shift of 4 bits */
	int32_t l1_phase = getles3224(buf, n + 6) / 16;
	uint8_t l1_slips = (uint8_t) (getles3224(buf, n + 6) & 0x0f);
	int16_t p1_ca_pseudorange = getles16(buf, n + 9);
	int16_t p2_ca_pseudorange = getles16(buf, n + 11);
	int32_t l2_phase = getles3224(buf, n + 13) / 16;
	uint8_t l2_slips = (uint8_t) (getles3224(buf, n + 13) & 0x0f);
	double c1 =
	    ((sv_status & 0x80) ? (double)ca_pseudorange / 16.0 *
	     LAMBDA_L1 : NAN);
	double l1 =
	    ((sv_status & 0x80) ? (double)ca_pseudorange / 16.0 +
	     (double)l1_phase / 256.0 : NAN);
	double l2 =
	    ((sv_status & 0x20)
	     ? ((double)ca_pseudorange / 16.0 +
		(double)p2_ca_pseudorange / 16.0) * (120.0 / 154.0)
	     + (double)l2_phase / 256.0 : NAN);
	double p1 =
	    ((sv_status & 0x40) ? c1 +
	     (double)p1_ca_pseudorange / 16.0 * LAMBDA_L1 : NAN);
	double p2 =
	    ((sv_status & 0x20) ? c1 +
	     (double)p2_ca_pseudorange / 16.0 * LAMBDA_L1 : NAN);
	GPSD_LOG(LOG_SPIN, &session->context->errout,
		 "Navcom: >> sv status = 0x%02x (PRN %u - C/A & L1 %s - P1 %s - P2 & L2 %s)\n",
		 sv_status, (sv_status & 0x1f),
		 ((sv_status & 0x80) ? "valid" : "invalid"),
		 ((sv_status & 0x40) ? "valid" : "invalid"),
		 ((sv_status & 0x20) ? "valid" : "invalid"));
	GPSD_LOG(LOG_SPIN, &session->context->errout,
		 "Navcom: >>> ch status = 0x%02x "
                 "(Logical channel: %u - CA C/No: %u dBHz) "
		 "sL1: %u, sL2: %u\n", ch_status, ch_status & 0x0f,
		 ((ch_status & 0xf0) >> 4) + 35, l1_slips, l2_slips);
	GPSD_LOG(LOG_SPIN, &session->context->errout,
		 "Navcom: >>> C1: %14.3f, L1: %14.3f, L2: %14.3f, P1: %14.3f, P2: %14.3f\n",
		 c1, l1, l2, p1, p2);
    }
#undef LAMBDA_L1
    return 0;			/* Raw measurements not yet implemented in gpsd */
}

/* Pseudorange Noise Statistics */
static gps_mask_t handle_0xb5(struct gps_device_t *session)
{
    if (sizeof(double) == 8) {
	gps_mask_t mask = TIME_SET;
	char *buf = (char *)session->lexer.outbuffer + 3;
	uint16_t week = getleu16(buf, 3);
	uint32_t tow = getleu32(buf, 5);
        timespec_t ts_tow;
#ifdef __UNUSED__
	double rms = getled64(buf, 9);
	/* Reason why it's unused is these figures do not agree
	 * with those obtained from the PVT report (handle_0xb1).
	 * The figures from 0xb1 do agree with the values reported
	 * by Navcom's PC utility */
        /* let gpsd_error_model() handle this */
	//double ellips_maj = getled64(buf, 17);
	//double ellips_min = getled64(buf, 25);
	//double ellips_azm = getled64(buf, 33);
	double lat_sd = getled64(buf, 41);
	double lon_sd = getled64(buf, 49);
	double alt_sd = getled64(buf, 57);
	double hrms = sqrt(pow(lat_sd, 2) + pow(lon_sd, 2));
        /* Navcom doc unclear, this is likely sep? */
	session->newdata.sep = rms * 1.96;
	session->newdata.eph = hrms * 1.96;
	session->newdata.epv = alt_sd * 1.96;
	mask |= HERR_SET;
#endif /*  __UNUSED__ */
	MSTOTS(&ts_tow, tow);
	session->newdata.time = gpsd_gpstime_resolv(session,
						  (unsigned short)week,
						  ts_tow);
	GPSD_LOG(LOG_PROG, &session->context->errout,
		 "Navcom: received packet type 0xb5 (Pseudorange Noise Statistics)\n");
	GPSD_LOG(LOG_DATA, &session->context->errout,
		 "Navcom: sep = %f\n", session->newdata.sep);
	return mask;
    } else {
	/* Ignore this message block */
	if (!session->driver.navcom.warned) {
	    GPSD_LOG(LOG_WARN, &session->context->errout,
		     "Navcom: received packet type 0xb5 (Pseudorange "
                     "Noise Statistics) ignored "
		     " - sizeof(double) == 64 bits required\n");
	    session->driver.navcom.warned = true;
	}
	return 0;		/* Block ignored - wrong sizeof(double) */
    }
}

/* LBM DSP Status Block */
static gps_mask_t handle_0xd3(struct gps_device_t *session UNUSED)
{
    /* This block contains status information about the
     * unit's L-band (Inmarsat) module.  There is nothing
     * interesting in it for our purposes so we do not deal
     * with it.  This callback is purely to a) stop
     * "unrecognised packet" messages appearing in the log
     * and b) explain what it is for the curious */
    return 0;			/* Nothing updated */
}

/* Identification Block */
static gps_mask_t handle_0xae(struct gps_device_t *session)
{
    char *engconfstr, *asicstr;
    unsigned char *buf = session->lexer.outbuffer + 3;
    size_t msg_len = (size_t) getleu16(buf, 1);
    uint8_t engconf = getub(buf, 3);
    uint8_t asic = getub(buf, 4);
    uint8_t swvermaj = getub(buf, 5);
    uint8_t swvermin = getub(buf, 6);
    uint16_t dcser = getleu16(buf, 7);
    uint8_t dcclass = getub(buf, 9);
    uint16_t rfcser = getleu16(buf, 10);
    uint8_t rfcclass = getub(buf, 12);
    uint8_t softtm[17] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    uint8_t bootstr[17] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    uint8_t ioptm[17] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    uint8_t iopvermaj = (uint8_t) 0x00;
    uint8_t iopvermin = (uint8_t) 0x00;
    uint8_t picver = (uint8_t) 0x00;
    uint8_t slsbn = (uint8_t) 0x00;
    uint8_t iopsbn = (uint8_t) 0x00;
    memcpy(softtm, &buf[13], 16);
    memcpy(bootstr, &buf[29], 16);
    if (msg_len == 0x0037) {	/* No IOP */
	slsbn = getub(buf, 53);
    } else {			/* IOP Present */
	iopvermaj = getub(buf, 53);
	iopvermin = getub(buf, 54);
	memcpy(ioptm, &buf[55], 16);
	picver = getub(buf, 71);
	slsbn = getub(buf, 72);
	iopsbn = getub(buf, 73);
    }

    switch (engconf) {
    case 0x00:
	engconfstr = "Unknown/Undefined";
	break;
    case 0x01:
	engconfstr = "NCT 2000 S";
	break;
    case 0x02:
	engconfstr = "NCT 2000 D";
	break;
    case 0x03:
	engconfstr = "Startfire Single";
	break;
    case 0x04:
	engconfstr = "Starfire Dual";
	break;
    case 0x05:
	engconfstr = "Pole Mount RTK (Internal Radio)";
	break;
    case 0x06:
	engconfstr = "Pole Mount GIS (LBM)";
	break;
    case 0x07:
	engconfstr = "Black Box RTK (Internal Radio)";
	break;
    case 0x08:
	engconfstr = "Black Box GIS (LBM)";
	break;
    case 0x80:
	engconfstr = "R100";
	break;
    case 0x81:
	engconfstr = "R200";
	break;
    case 0x82:
	engconfstr = "R210";
	break;
    case 0x83:
	engconfstr = "R300";
	break;
    case 0x84:
	engconfstr = "R310";
	break;
    default:
	engconfstr = "?";
    }

    switch (asic) {
    case 0x01:
	asicstr = "A-ASIC";
	break;
    case 0x02:
	asicstr = "B-ASIC";
	break;
    case 0x03:
	asicstr = "C-ASIC";
	break;
    case 0x04:
	asicstr = "M-ASIC";
	break;
    default:
	asicstr = "?";
    }

    GPSD_LOG(LOG_PROG, &session->context->errout,
	     "Navcom: received packet type 0xae (Identification Block)\n");
    if (msg_len == 0x0037) {
	GPSD_LOG(LOG_INF, &session->context->errout, "Navcom: ID Data: "
		 "%s %s Ver. %u.%u.%u, DC S/N: %u.%u, RF S/N: %u.%u, "
		 "Build ID: %s, Boot software: %s\n",
		 engconfstr, asicstr, swvermaj, swvermin, slsbn, dcser,
		 dcclass, rfcser, rfcclass, softtm, bootstr);
    } else {
	GPSD_LOG(LOG_INF, &session->context->errout, "Navcom: ID Data: "
		 "%s %s Ver. %u.%u.%u, DC S/N: %u.%u, RF S/N: %u.%u, "
		 "Build ID: %s, Boot software: %s, "
		 "IOP Ver.: %u.%u.%u, PIC: %u, IOP Build ID: %s\n",
		 engconfstr, asicstr, swvermaj, swvermin, slsbn, dcser,
		 dcclass, rfcser, rfcclass, softtm, bootstr, iopvermaj,
		 iopvermin, iopsbn, picver, ioptm);
    }

    (void)snprintf(session->subtype, sizeof(session->subtype),
		   "%s %s Ver. %u.%u.%u S/N %u.%u %u.%u",
		   engconfstr, asicstr, swvermaj, swvermin, slsbn, dcser,
		   dcclass, rfcser, rfcclass);
    return DEVICEID_SET;
}

/* Clock Drift and Offset */
static gps_mask_t handle_0xef(struct gps_device_t *session)
{
    unsigned char *buf = session->lexer.outbuffer + 3;
    //uint16_t week = getleu16(buf, 3);
    //uint32_t tow = getleu32(buf, 5);
    int8_t osc_temp = getsb(buf, 9);
    uint8_t nav_status = getub(buf, 10);
    double nav_clock_offset;
    float nav_clock_drift;
    float osc_filter_drift_est;
    char ts_buf[TIMESPEC_LEN];
    int32_t time_slew = (int32_t) getles32(buf, 27);
    if (sizeof(double) == 8) {
	nav_clock_offset = getled64((char *)buf, 11);
    } else {
	nav_clock_offset = NAN;
    }
    if (sizeof(float) == 4) {
	nav_clock_drift = getlef32((char *)buf, 19);
	osc_filter_drift_est = getlef32((char *)buf, 23);
    } else {
	nav_clock_drift = NAN;
	osc_filter_drift_est = NAN;
    }

    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "Navcom: oscillator temp. = %d, nav. status = 0x%02x, "
	     "nav. clock offset = %f, nav. clock drift = %f, "
	     "osc. filter drift est. = %f, acc.time slew value = %d\n",
	     osc_temp, nav_status, nav_clock_offset, nav_clock_drift,
	     osc_filter_drift_est, time_slew);
    GPSD_LOG(LOG_DATA, &session->context->errout,
	     "CDO 0xef: time=%s mask={TIME}\n",
             timespec_str(&session->newdata.time, ts_buf, sizeof(ts_buf)));
    return 0;
}


gps_mask_t navcom_parse(struct gps_device_t * session, unsigned char *buf,
			size_t len)
{
    unsigned char cmd_id;
    unsigned int msg_len;

    if (len == 0)
	return 0;

    cmd_id = (unsigned char)getub(buf, 3);
    //payload = &buf[6];
    msg_len = (unsigned int) getleu16(buf, 4);

    GPSD_LOG(LOG_RAW, &session->context->errout,
	     "Navcom: packet type 0x%02x\n", cmd_id);

    session->cycle_end_reliable = true;

    switch (cmd_id) {
    case 0x06:
	return handle_0x06(session);
    case 0x15:
	return handle_0x15(session);
    case 0x81:
	return handle_0x81(session);
    case 0x83:
	return handle_0x83(session);
    case 0x86:
	return handle_0x86(session);
    case 0xae:
	return handle_0xae(session);
    case 0xb0:
	return handle_0xb0(session);
    case 0xb1:
	return handle_0xb1(session) | (CLEAR_IS | REPORT_IS);
    case 0xb5:
	return handle_0xb5(session);
    case 0xd3:
	return handle_0xd3(session);
    case 0xef:
	return handle_0xef(session);
    default:
	GPSD_LOG(LOG_PROG, &session->context->errout,
		 "Navcom: received packet type 0x%02x, length %d - "
                 "unknown or unimplemented\n",
		 cmd_id, msg_len);
	return 0;
    }
}


static gps_mask_t navcom_parse_input(struct gps_device_t *session)
{
    if (session->lexer.type == NAVCOM_PACKET) {
	return navcom_parse(session, session->lexer.outbuffer,
			  session->lexer.outbuflen);
#ifdef NMEA0183_ENABLE
    } else if (session->lexer.type == NMEA_PACKET) {
	return nmea_parse((char *)session->lexer.outbuffer, session);;
#endif /* NMEA0183_ENABLE */
    } else
	return 0;
}

#ifdef CONTROLSEND_ENABLE
static ssize_t navcom_control_send(struct gps_device_t *session,
				   char *buf, size_t len)
{
    putbyte(session->msgbuf, 0, 0x02);
    putbyte(session->msgbuf, 1, 0x99);
    putbyte(session->msgbuf, 2, 0x66);
    putbyte(session->msgbuf, 3, buf[0]);	/* Cmd ID */
    putle16(session->msgbuf, 4, len + 4);	/* Length */
    memcpy(session->msgbuf, buf + 6, len - 1);
    putbyte(session->msgbuf, 6 + len,
	    checksum((unsigned char *)session->msgbuf + 3, len + 5));
    putbyte(session->msgbuf, 7 + len, 0x03);
    session->msgbuflen = len + 9;
    return gpsd_write(session, session->msgbuf, session->msgbuflen);
}
#endif /* CONTROLSEND_ENABLE */

#ifdef RECONFIGURE_ENABLE
static bool navcom_speed(struct gps_device_t *session,
			 speed_t speed, char parity, int stopbits)
{
    /* parity and stopbit switching aren't implemented */
    if (parity != session->gpsdata.dev.parity
	|| stopbits != (int)session->gpsdata.dev.parity) {
	return false;
    } else {
	uint8_t port, port_selection;
	uint8_t baud;
	if (session->driver.navcom.physical_port == (uint8_t) 0xFF) {
	    /* We still don't know which port we're connected to */
	    return false;
	}
	switch (speed) {
	    /* NOTE - The spec says that certain baud combinations
	     * on ports A and B are not allowed, those are
	     * 1200/115200, 2400/57600, and 2400/115200.
	     * To try and minimise the possibility of those
	     * occurring, we do not allow baud rates below
	     * 4800.  We could also disallow 57600 and 115200
	     * to totally prevent this, but I do not consider
	     * that reasonable.  Finding which baud speed the
	     * other port is set at would also be too much
	     * trouble, so we do not do it. */
	case 4800:
	    baud = 0x04;
	    break;
	case 9600:
	    baud = 0x06;
	    break;
	case 19200:
	    baud = 0x08;
	    break;
	case 38400:
	    baud = 0x0a;
	    break;
	case 57600:
	    baud = 0x0c;
	    break;
	case 115200:
	    baud = 0x0e;
	    break;
	default:
	    /* Unsupported speed */
	    return false;
	}

	/* Proceed to construct our message */
	port = session->driver.navcom.physical_port;
	port_selection = (port ? port : (uint8_t) 0xff) | baud;

	/* Send it off */
	navcom_cmd_0x11(session, port_selection);

	/* And cheekily return true, even though we have
	 * no way to know if the speed change succeeded
	 * until and if we receive an ACK (message 0x06),
	 * which will be at the new baud speed if the
	 * command was successful.  Bottom line, the client
	 * should requery gpsd to see if the new speed is
	 * different than the old one */
	return true;
    }
}
#endif /* RECONFIGURE_ENABLE */

/* this is everything we export */
/* *INDENT-OFF* */
const struct gps_type_t driver_navcom =
{
    .type_name      = "Navcom NCT",		/* full name of type */
    .packet_type    = NAVCOM_PACKET,		/* lexer packet type */
    .flags	    = DRIVER_STICKY,		/* remember this */
    .trigger	    = NULL,			/* none */
    .channels       = NAVCOM_CHANNELS,		/* 12 L1 + 12 L2 + 2 Inmarsat L-Band */
    .probe_detect   = NULL,			/* no probe */
    .get_packet     = generic_get,		/* use generic one */
    .parse_packet   = navcom_parse_input,	/* parse message packets */
    .rtcm_writer    = gpsd_write,		/* send RTCM data straight */
    .init_query     = NULL,			/* non-perturbing query */
    .event_hook     = navcom_event_hook,	/* lifetime event handler */
#ifdef RECONFIGURE_ENABLE
    .speed_switcher = navcom_speed,		/* we do change baud rates */
    .mode_switcher  = NULL,			/* there is not a mode switcher */
    .rate_switcher  = NULL,			/* no sample-rate switcher */
    .min_cycle.tv_sec  = 1,		/* not relevant, no rate switch */
    .min_cycle.tv_nsec = 0,		/* not relevant, no rate switch */
#endif /* RECONFIGURE_ENABLE */
#ifdef CONTROLSEND_ENABLE
    .control_send   = navcom_control_send,	/* how to send a control string */
#endif /* CONTROLSEND_ENABLE */
    .time_offset     = NULL,		/* no method for NTP fudge factor */
};
/* *INDENT-ON* */

#endif /* defined(NAVCOM_ENABLE) */
