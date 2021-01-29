/*
 * monitor_nmea0183.c - gpsmon support for NMEA devices.
 *
 * To do: Support for GPGLL, GPGBS, GPZDA, PASHR NMEA sentences.
 *
 * This file is Copyright (c) 2010 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 */

/* for vsnprintf() FreeBSD wants __ISO_C_VISIBLE >= 1999 */
#define __ISO_C_VISIBLE 1999

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h> /* for labs() */
#include <assert.h>
#include <stdarg.h>
#include <unistd.h>

#include "gpsd.h"
#include "gpsmon.h"
#include "gpsdclient.h"
#include "strfuncs.h"

#ifdef NMEA0183_ENABLE
extern const struct gps_type_t driver_nmea0183;

static WINDOW *cookedwin, *nmeawin, *satwin, *gprmcwin, *gpggawin, *gpgsawin, *gpgstwin;
static timestamp_t last_tick, tick_interval;
static char sentences[NMEA_MAX * 2];

/*****************************************************************************
 *
 * NMEA0183 support
 *
 *****************************************************************************/

#define SENTENCELINE	1	/* index of sentences line in the NMEA window */
#define MAXSATS 	12	/* max satellites we can display */

static bool nmea_initialize(void)
{
    int i;

    cookedwin = derwin(devicewin, 3, 80, 0, 0);
    assert(cookedwin !=NULL);
    (void)wborder(cookedwin, 0, 0, 0, 0, 0, 0, 0, 0);
    (void)syncok(cookedwin, true);
    (void)wattrset(cookedwin, A_BOLD);
    (void)mvwaddstr(cookedwin, 1, 1, "Time: ");
    (void)mvwaddstr(cookedwin, 1, 32, "Lat: ");
    (void)mvwaddstr(cookedwin, 1, 55, "Lon: ");
    (void)mvwaddstr(cookedwin, 2, 34, " Cooked TPV ");
    (void)wattrset(cookedwin, A_NORMAL);

    nmeawin = derwin(devicewin, 3, 80, 3, 0);
    assert(nmeawin !=NULL);
    (void)wborder(nmeawin, 0, 0, 0, 0, 0, 0, 0, 0);
    (void)syncok(nmeawin, true);
    (void)wattrset(nmeawin, A_BOLD);
    (void)mvwaddstr(nmeawin, 2, 34, " Sentences ");
    (void)wattrset(nmeawin, A_NORMAL);

    satwin = derwin(devicewin, MAXSATS + 3, 20, 6, 0);
    assert(satwin !=NULL);
    (void)wborder(satwin, 0, 0, 0, 0, 0, 0, 0, 0), (void)syncok(satwin, true);
    (void)wattrset(satwin, A_BOLD);
    (void)mvwprintw(satwin, 1, 1, "Ch PRN  Az El S/N");
    for (i = 0; i < MAXSATS; i++)
	(void)mvwprintw(satwin, (int)(i + 2), 1, "%2d", i);
    (void)mvwprintw(satwin, 14, 7, " GSV ");
    (void)wattrset(satwin, A_NORMAL);

    gprmcwin = derwin(devicewin, 9, 30, 6, 20);
    assert(gprmcwin !=NULL);
    (void)wborder(gprmcwin, 0, 0, 0, 0, 0, 0, 0, 0),
	(void)syncok(gprmcwin, true);
    (void)wattrset(gprmcwin, A_BOLD);
    (void)mvwprintw(gprmcwin, 1, 1, "Time: ");
    (void)mvwprintw(gprmcwin, 2, 1, "Latitude: ");
    (void)mvwprintw(gprmcwin, 3, 1, "Longitude: ");
    (void)mvwprintw(gprmcwin, 4, 1, "Speed: ");
    (void)mvwprintw(gprmcwin, 5, 1, "Course: ");
    (void)mvwprintw(gprmcwin, 6, 1, "Status:            FAA: ");
    (void)mvwprintw(gprmcwin, 7, 1, "MagVar: ");
    (void)mvwprintw(gprmcwin, 8, 12, " RMC ");
    (void)wattrset(gprmcwin, A_NORMAL);

    gpgsawin = derwin(devicewin, 6, 30, 15, 20);
    assert(gpgsawin !=NULL);
    (void)wborder(gpgsawin, 0, 0, 0, 0, 0, 0, 0, 0);
    (void)syncok(gpgsawin, true);
    (void)wattrset(gpgsawin, A_BOLD);
#define MODE_LINE	1
    (void)mvwprintw(gpgsawin, MODE_LINE, 1, "Mode: ");
#define SATS_LINE	1
#define SATS_COL	10
    (void)mvwprintw(gpgsawin, SATS_LINE, SATS_COL, "Sats: ");
#define DOP_LINE	2
    (void)mvwprintw(gpgsawin, DOP_LINE, 1, "DOP: H=      V=      P=");
#define TOFF_LINE	3
    (void)mvwprintw(gpgsawin, TOFF_LINE, 1, "TOFF: ");
#ifndef PPS_ENABLE
    (void)mvwaddstr(gpgsawin, TOFF_LINE, 7, "N/A");
#endif /* PPS_ENABLE */
#define PPS_LINE	4
    (void)mvwprintw(gpgsawin, PPS_LINE, 1, "PPS: ");
#ifndef PPS_ENABLE
    (void)mvwaddstr(gpgsawin, PPS_LINE, 6, "N/A");
#endif /* PPS_ENABLE */
    (void)mvwprintw(gpgsawin, 5, 9, " GSA + PPS ");
    (void)wattrset(gpgsawin, A_NORMAL);
    (void)syncok(gpgsawin, true);

    gpggawin = derwin(devicewin, 9, 30, 6, 50);
    assert(gpggawin !=NULL);
    (void)wborder(gpggawin, 0, 0, 0, 0, 0, 0, 0, 0);
    (void)syncok(gpggawin, true);
    (void)wattrset(gpggawin, A_BOLD);
    (void)mvwprintw(gpggawin, 1, 1, "Time: ");
    (void)mvwprintw(gpggawin, 2, 1, "Latitude: ");
    (void)mvwprintw(gpggawin, 3, 1, "Longitude: ");
    (void)mvwprintw(gpggawin, 4, 1, "Altitude: ");
    (void)mvwprintw(gpggawin, 5, 1, "Quality:       Sats: ");
    (void)mvwprintw(gpggawin, 6, 1, "HDOP: ");
    (void)mvwprintw(gpggawin, 7, 1, "Geoid: ");
    (void)mvwprintw(gpggawin, 8, 12, " GGA ");
    (void)wattrset(gpggawin, A_NORMAL);

    gpgstwin = derwin(devicewin, 6, 30, 15, 50);
    assert(gpgstwin !=NULL);
    (void)wborder(gpgstwin, 0, 0, 0, 0, 0, 0, 0, 0);
    (void)syncok(gpgstwin, true);
    (void)wattrset(gpgstwin, A_BOLD);
    (void)mvwprintw(gpgstwin, 1,  1, "UTC: ");
    (void)mvwprintw(gpgstwin, 1, 16, "RMS: ");
    (void)mvwprintw(gpgstwin, 2,  1, "MAJ: ");
    (void)mvwprintw(gpgstwin, 2, 16, "MIN: ");
    (void)mvwprintw(gpgstwin, 3,  1, "ORI: ");
    (void)mvwprintw(gpgstwin, 3, 16, "LAT: ");
    (void)mvwprintw(gpgstwin, 4,  1, "LON: ");
    (void)mvwprintw(gpgstwin, 4, 16, "ALT: ");
    (void)mvwprintw(gpgstwin, 5, 12, " GST ");
    (void)wattrset(gpgstwin, A_NORMAL);


    last_tick = timestamp();

    sentences[0] = '\0';

    return (nmeawin != NULL);
}

static void cooked_pvt(void)
{
    char scr[128];

    if (isnan(session.gpsdata.fix.time) == 0) {
	(void)unix_to_iso8601(session.gpsdata.fix.time, scr, sizeof(scr));
    } else
	(void)snprintf(scr, sizeof(scr), "n/a");
    (void)mvwprintw(cookedwin, 1, 7, "%-24s", scr);


    if (session.gpsdata.fix.mode >= MODE_2D
	&& isnan(session.gpsdata.fix.latitude) == 0) {
	(void)snprintf(scr, sizeof(scr), "%s %c",
		       deg_to_str(deg_ddmmss,
				  fabs(session.gpsdata.fix.latitude)),
		       (session.gpsdata.fix.latitude < 0) ? 'S' : 'N');
    } else
	(void)snprintf(scr, sizeof(scr), "n/a");
    (void)mvwprintw(cookedwin, 1, 37, "%-17s", scr);

    if (session.gpsdata.fix.mode >= MODE_2D
	&& isnan(session.gpsdata.fix.longitude) == 0) {
	(void)snprintf(scr, sizeof(scr), "%s %c",
		       deg_to_str(deg_ddmmss,
				  fabs(session.gpsdata.fix.longitude)),
		       (session.gpsdata.fix.longitude < 0) ? 'W' : 'E');
    } else
	(void)snprintf(scr, sizeof(scr), "n/a");
    (void)mvwprintw(cookedwin, 1, 60, "%-17s", scr);
}

static void monitor_satlist(WINDOW *win, int y, int x)
/* display as much as we can of a satlist in a specified window */
{
    int ymax, xmax;
    char scr[128];
    int i;

    assert(win != NULL);
    (void)wmove(win, y, x);
    (void)wclrtoeol(win);
    scr[0] = '\0';
    for (i = 0; i < MAXCHANNELS; i++) {
	if (session.gpsdata.skyview[i].used)
	    str_appendf(scr, sizeof(scr),
			"%d ", session.gpsdata.skyview[i].PRN);
    }
    getmaxyx(win, ymax, xmax);
    assert(ymax != 0);	/* suppress compiler warning */
    (void)mvwaddnstr(win, y, x, scr, xmax - 2 - x);
    if (strlen(scr) >= (size_t) (xmax - 2)) {
	(void)mvwaddch(win, y, xmax - 2 - x, (chtype) '.');
	(void)mvwaddch(win, y, xmax - 3 - x, (chtype) '.');
	(void)mvwaddch(win, y, xmax - 4 - x, (chtype) '.');
    }
    monitor_fixframe(win);
}

static void nmea_update(void)
{
    char **fields;

    assert(cookedwin != NULL);
    assert(nmeawin != NULL);
    assert(gpgsawin != NULL);
    assert(gpggawin != NULL);
    assert(gprmcwin != NULL);
    assert(gpgstwin != NULL);

    /* can be NULL if packet was overlong */
    fields = session.nmea.field;

    if (session.lexer.outbuffer[0] == (unsigned char)'$'
		&& fields != NULL && fields[0] != NULL) {
	int ymax, xmax;
	timestamp_t now;
	getmaxyx(nmeawin, ymax, xmax);
	assert(ymax > 0);
	if (strstr(sentences, fields[0]) == NULL) {
	    char *s_end = sentences + strlen(sentences);
	    if ((int)(strlen(sentences) + strlen(fields[0])) < xmax - 2) {
		*s_end++ = ' ';
		(void)strlcpy(s_end, fields[0], NMEA_MAX);
	    } else {
		*--s_end = '.';
		*--s_end = '.';
		*--s_end = '.';
	    }
	    (void)mvwaddstr(nmeawin, SENTENCELINE, 1, sentences);
	}

	/*
	 * If the interval between this and last update is
	 * the longest we've seen yet, boldify the corresponding
	 * tag.
	 */
	now = timestamp();
	if (now > last_tick && (now - last_tick) > tick_interval) {
	    char *findme = strstr(sentences, fields[0]);

	    tick_interval = now - last_tick;
	    if (findme != NULL) {
		(void)mvwchgat(nmeawin, SENTENCELINE, 1, xmax - 13, A_NORMAL, 0,
			       NULL);
		(void)mvwchgat(nmeawin, SENTENCELINE, 1 + (findme - sentences),
			       (int)strlen(fields[0]), A_BOLD, 0, NULL);
	    }
	}
	last_tick = now;

	if (strcmp(fields[0], "GPGSV") == 0
	    || strcmp(fields[0], "GNGSV") == 0
	    || strcmp(fields[0], "GLGSV") == 0) {
	    int i;
	    int nsats =
		(session.gpsdata.satellites_visible <
		 MAXSATS) ? session.gpsdata.satellites_visible : MAXSATS;

	    for (i = 0; i < nsats; i++) {
		(void)wmove(satwin, i + 2, 3);
		(void)wprintw(satwin, " %3d %3d%3d %3.0f",
			      session.gpsdata.skyview[i].PRN,
			      session.gpsdata.skyview[i].azimuth,
			      session.gpsdata.skyview[i].elevation,
			      session.gpsdata.skyview[i].ss);
	    }
	    /* add overflow mark to the display */
	    if (nsats <= MAXSATS)
		(void)mvwaddch(satwin, MAXSATS + 2, 18, ACS_HLINE);
	    else
		(void)mvwaddch(satwin, MAXSATS + 2, 18, ACS_DARROW);
	}

	if (strcmp(fields[0], "GPRMC") == 0
	    || strcmp(fields[0], "GNRMC") == 0
	    || strcmp(fields[0], "GLRMC") == 0) {
	    /* time, lat, lon, course, speed */
	    (void)mvwaddstr(gprmcwin, 1, 12, fields[1]);
	    (void)mvwprintw(gprmcwin, 2, 12, "%12s %s", fields[3], fields[4]);
	    (void)mvwprintw(gprmcwin, 3, 12, "%12s %s", fields[5], fields[6]);
	    (void)mvwaddstr(gprmcwin, 4, 12, fields[7]);
	    (void)mvwaddstr(gprmcwin, 5, 12, fields[8]);
	    /* the status field, FAA code, and magnetic variation */
	    (void)mvwaddstr(gprmcwin, 6, 12, fields[2]);
	    (void)mvwaddstr(gprmcwin, 6, 25, fields[12]);
	    (void)mvwprintw(gprmcwin, 7, 12, "%-5s%s", fields[10],
			    fields[11]);

	    cooked_pvt();	/* cooked version of TPV */
	}

	if (strcmp(fields[0], "GPGSA") == 0
	    || strcmp(fields[0], "GNGSA") == 0
	    || strcmp(fields[0], "GLGSA") == 0) {
	    (void)mvwprintw(gpgsawin, MODE_LINE, 7, "%1s%s", fields[1], fields[2]);
	    monitor_satlist(gpgsawin, SATS_LINE, SATS_COL+6);
	    (void)mvwprintw(gpgsawin, DOP_LINE, 8, "%-5s", fields[16]);
	    (void)mvwprintw(gpgsawin, DOP_LINE, 16, "%-5s", fields[17]);
	    (void)mvwprintw(gpgsawin, DOP_LINE, 24, "%-5s", fields[15]);
	    monitor_fixframe(gpgsawin);
	}

#ifdef NTP_ENABLE
	toff_update(gpgsawin, TOFF_LINE, 7);
#endif /* NTP_ENABLE */

	if (strcmp(fields[0], "GPGGA") == 0
	    || strcmp(fields[0], "GNGGA") == 0
	    || strcmp(fields[0], "GLGGA") == 0) {
	    (void)mvwprintw(gpggawin, 1, 12, "%-17s", fields[1]);
	    (void)mvwprintw(gpggawin, 2, 12, "%-17s", fields[2]);
	    (void)mvwprintw(gpggawin, 3, 12, "%-17s", fields[4]);
	    (void)mvwprintw(gpggawin, 4, 12, "%-17s", fields[9]);
	    (void)mvwprintw(gpggawin, 5, 12, "%1.1s", fields[6]);
	    (void)mvwprintw(gpggawin, 5, 22, "%2.2s", fields[7]);
	    (void)mvwprintw(gpggawin, 6, 12, "%-5.5s", fields[8]);
	    (void)mvwprintw(gpggawin, 7, 12, "%-5.5s", fields[11]);
	}
	if (strcmp(fields[0], "GPGST") == 0) {
	    (void)mvwprintw(gpgstwin, 1,  6, "%-10s", fields[1]);
	    (void)mvwprintw(gpgstwin, 1, 21,  "%-8s", fields[2]);
	    (void)mvwprintw(gpgstwin, 2,  6, "%-10s", fields[3]);
	    (void)mvwprintw(gpgstwin, 2, 21,  "%-8s", fields[4]);
	    (void)mvwprintw(gpgstwin, 3,  6, "%-10s", fields[5]);
	    (void)mvwprintw(gpgstwin, 3, 21,  "%-8s", fields[6]);
	    (void)mvwprintw(gpgstwin, 4,  6, "%-10s", fields[7]);
	    (void)mvwprintw(gpgstwin, 4, 21,  "%-8s", fields[8]);
	}
    }

#ifdef PPS_ENABLE
    pps_update(gpgsawin, PPS_LINE, 6);
#endif /* PPS_ENABLE */
}

#undef SENTENCELINE

static void nmea_wrap(void)
{
    (void)delwin(nmeawin);
    (void)delwin(gpgsawin);
    (void)delwin(gpggawin);
    (void)delwin(gprmcwin);
}

const struct monitor_object_t nmea_mmt = {
    .initialize = nmea_initialize,
    .update = nmea_update,
    .command = NULL,
    .wrap = nmea_wrap,
    .min_y = 21,.min_x = 80,
    .driver = &driver_nmea0183,
};

/*****************************************************************************
 *
 * Extended NMEA support
 *
 *****************************************************************************/

#if defined(CONTROLSEND_ENABLE) && defined(ASHTECH_ENABLE)
static void monitor_nmea_send(const char *fmt, ...)
{
    char buf[BUFSIZ];
    va_list ap;

    va_start(ap, fmt);
    (void)vsnprintf(buf, sizeof(buf) - 5, fmt, ap);
    va_end(ap);
    (void)monitor_control_send((unsigned char *)buf, strlen(buf));
}
#endif /* defined(CONTROLSEND_ENABLE) && defined(ASHTECH_ENABLE) */

/*
 * Yes, it's OK for most of these to be clones of the generic NMEA monitor
 * object except for the pointer to the GPSD driver.  That pointer makes
 * a difference, as it will automatically enable stuff like speed-switcher
 * and mode-switcher commands.  It's really only necessary to write a
 * separate monitor object if you want to change the device-window
 * display or implement device-specific commands.
 */

#if defined(GARMIN_ENABLE) && defined(NMEA0183_ENABLE)
extern const struct gps_type_t driver_garmin;

const struct monitor_object_t garmin_mmt = {
    .initialize = nmea_initialize,
    .update = nmea_update,
    .command = NULL,
    .wrap = nmea_wrap,
    .min_y = 21,.min_x = 80,
    .driver = &driver_garmin,
};
#endif /* GARMIN_ENABLE && NMEA0183_ENABLE */

#ifdef ASHTECH_ENABLE
extern const struct gps_type_t driver_ashtech;

#define ASHTECH_SPEED_9600 5
#define ASHTECH_SPEED_57600 8

#ifdef CONTROLSEND_ENABLE
static int ashtech_command(char line[])
{
    switch (line[0]) {
    case 'N':			/* normal = 9600, GGA+GSA+GSV+RMC+ZDA */
	monitor_nmea_send("$PASHS,NME,ALL,A,OFF");	/* silence outbound chatter */
	monitor_nmea_send("$PASHS,NME,ALL,B,OFF");
	monitor_nmea_send("$PASHS,NME,GGA,A,ON");
	monitor_nmea_send("$PASHS,NME,GSA,A,ON");
	monitor_nmea_send("$PASHS,NME,GSV,A,ON");
	monitor_nmea_send("$PASHS,NME,RMC,A,ON");
	monitor_nmea_send("$PASHS,NME,ZDA,A,ON");

	monitor_nmea_send("$PASHS,INI,%d,%d,,,0,",
			  ASHTECH_SPEED_9600, ASHTECH_SPEED_9600);
	(void)sleep(6);		/* it takes 4-6 sec for the receiver to reboot */
	monitor_nmea_send("$PASHS,WAS,ON");	/* enable WAAS */
	break;

    case 'R':			/* raw = 57600, normal+XPG+POS+SAT+MCA+PBN+SNV */
	monitor_nmea_send("$PASHS,NME,ALL,A,OFF");	/* silence outbound chatter */
	monitor_nmea_send("$PASHS,NME,ALL,B,OFF");
	monitor_nmea_send("$PASHS,NME,GGA,A,ON");
	monitor_nmea_send("$PASHS,NME,GSA,A,ON");
	monitor_nmea_send("$PASHS,NME,GSV,A,ON");
	monitor_nmea_send("$PASHS,NME,RMC,A,ON");
	monitor_nmea_send("$PASHS,NME,ZDA,A,ON");

	monitor_nmea_send("$PASHS,INI,%d,%d,,,0,",
			  ASHTECH_SPEED_57600, ASHTECH_SPEED_9600);
	(void)sleep(6);		/* it takes 4-6 sec for the receiver to reboot */
	monitor_nmea_send("$PASHS,WAS,ON");	/* enable WAAS */

	monitor_nmea_send("$PASHS,NME,POS,A,ON");	/* Ashtech TPV solution */
	monitor_nmea_send("$PASHS,NME,SAT,A,ON");	/* Ashtech Satellite status */
	monitor_nmea_send("$PASHS,NME,MCA,A,ON");	/* MCA measurements */
	monitor_nmea_send("$PASHS,NME,PBN,A,ON");	/* ECEF TPV solution */
	monitor_nmea_send("$PASHS,NME,SNV,A,ON,10");	/* Almanac data */

	monitor_nmea_send("$PASHS,NME,XMG,A,ON");	/* exception messages */
	break;

    default:
	return COMMAND_UNKNOWN;
    }

    return COMMAND_UNKNOWN;
}
#endif /* CONTROLSEND_ENABLE */

const struct monitor_object_t ashtech_mmt = {
    .initialize = nmea_initialize,
    .update = nmea_update,
#ifdef CONTROLSEND_ENABLE
    .command = ashtech_command,
#else
    .command = NULL,
#endif /* CONTROLSEND_ENABLE */
    .wrap = nmea_wrap,
    .min_y = 21,.min_x = 80,
    .driver = &driver_ashtech,
};
#endif /* ASHTECH_ENABLE */

#ifdef FV18_ENABLE
extern const struct gps_type_t driver_fv18;

const struct monitor_object_t fv18_mmt = {
    .initialize = nmea_initialize,
    .update = nmea_update,
    .command = NULL,
    .wrap = nmea_wrap,
    .min_y = 21,.min_x = 80,
    .driver = &driver_fv18,
};
#endif /* FV18_ENABLE */

#ifdef GPSCLOCK_ENABLE
extern const struct gps_type_t driver_gpsclock;

const struct monitor_object_t gpsclock_mmt = {
    .initialize = nmea_initialize,
    .update = nmea_update,
    .command = NULL,
    .wrap = nmea_wrap,
    .min_y = 21,.min_x = 80,
    .driver = &driver_gpsclock,
};
#endif /* GPSCLOCK_ENABLE */

#ifdef MTK3301_ENABLE
extern const struct gps_type_t driver_mtk3301;

const struct monitor_object_t mtk3301_mmt = {
    .initialize = nmea_initialize,
    .update = nmea_update,
    .command = NULL,
    .wrap = nmea_wrap,
    .min_y = 21,.min_x = 80,
    .driver = &driver_mtk3301,
};
#endif /* MTK3301_ENABLE */

#ifdef AIVDM_ENABLE
extern const struct gps_type_t driver_aivdm;

const struct monitor_object_t aivdm_mmt = {
    .initialize = nmea_initialize,
    .update = nmea_update,
    .command = NULL,
    .wrap = nmea_wrap,
    .min_y = 21,.min_x = 80,
    .driver = &driver_aivdm,
};
#endif /* AIVDM_ENABLE */
#endif /* NMEA0183_ENABLE */
