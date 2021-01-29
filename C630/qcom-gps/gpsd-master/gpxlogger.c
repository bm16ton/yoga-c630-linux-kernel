/*
 * This file is Copyright (c) 2010-2018 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 */

#include "gpsd_config.h"  /* must be before all includes */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <errno.h>
#include <libgen.h>
#include <signal.h>
#include <assert.h>
#include <unistd.h>

#include "gps.h"
#include "gpsdclient.h"
#include "revision.h"
#include "os_compat.h"
#include "timespec.h"

static char *progname;
static struct fixsource_t source;

/**************************************************************************
 *
 * Transport-layer-independent functions
 *
 **************************************************************************/

static struct gps_data_t gpsdata;
static FILE *logfile;
static bool intrack = false;
static time_t timeout = 5;	/* seconds */
static double minmove = 0;	/* meters */
#ifdef CLIENTDEBUG_ENABLE
static int debug;
#endif /* CLIENTDEBUG_ENABLE */

static void print_gpx_header(void)
{
    char tbuf[CLIENT_DATE_MAX+1];

    (void)fprintf(logfile, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
    (void)fprintf(logfile, "<gpx version=\"1.1\" creator=\"GPSD %s - %s\"\n",
                  VERSION, GPSD_URL);
    (void)fprintf(logfile,
         "        xmlns:xsi=\"https://www.w3.org/2001/XMLSchema-instance\"\n");
    (void)fprintf(logfile,
         "        xmlns=\"http://www.topografix.com/GPX/1/1\"\n");
    (void)fprintf(logfile
         ,"        xsi:schemaLocation=\"http://www.topografix.com/GPX/1/1\n");
    (void)fprintf(logfile
         ,"        http://www.topografix.com/GPX/1/1/gpx.xsd\">\n");
    (void)fprintf(logfile, " <metadata>\n");
    (void)fprintf(logfile, "  <time>%s</time>\n",
         now_to_iso8601(tbuf, sizeof(tbuf)));
    (void)fprintf(logfile," </metadata>\n");
    (void)fflush(logfile);
}

static void print_gpx_trk_end(void)
{
    (void)fprintf(logfile,"  </trkseg>\n");
    (void)fprintf(logfile," </trk>\n");
    (void)fflush(logfile);
}

static void print_gpx_footer(void)
{
    if (intrack)
	print_gpx_trk_end();
    (void)fprintf(logfile,"</gpx>\n");
    (void)fclose(logfile);
}

static void print_gpx_trk_start(void)
{
    (void)fprintf(logfile," <trk>\n");
    (void)fprintf(logfile,"  <src>GPSD %s</src>\n", VERSION);
    (void)fprintf(logfile,"  <trkseg>\n");
    (void)fflush(logfile);
}

static void print_fix(struct gps_data_t *gpsdata, timespec_t ts_time)
{
    char tbuf[CLIENT_DATE_MAX+1];

    /* lat/lon/ele are all WGS84, no altMSL */
    (void)fprintf(logfile,"   <trkpt lat=\"%f\" lon=\"%f\">\n",
		 gpsdata->fix.latitude, gpsdata->fix.longitude);
    if ((isfinite(gpsdata->fix.altHAE) != 0))
	(void)fprintf(logfile,"    <ele>%f</ele>\n", gpsdata->fix.altHAE);
    (void)fprintf(logfile,"    <time>%s</time>\n",
		 timespec_to_iso8601(ts_time, tbuf, sizeof(tbuf)));
    if (gpsdata->status == STATUS_DGPS_FIX)
	(void)fprintf(logfile,"    <fix>dgps</fix>\n");
    else
	switch (gpsdata->fix.mode) {
	case MODE_3D:
	    (void)fprintf(logfile,"    <fix>3d</fix>\n");
	    break;
	case MODE_2D:
	    (void)fprintf(logfile,"    <fix>2d</fix>\n");
	    break;
	case MODE_NO_FIX:
	    (void)fprintf(logfile,"    <fix>none</fix>\n");
	    break;
	default:
	    /* don't print anything if no fix indicator */
	    break;
	}

    if ((gpsdata->fix.mode > MODE_NO_FIX) && (gpsdata->satellites_used > 0))
	(void)fprintf(logfile,"    <sat>%d</sat>\n", gpsdata->satellites_used);
    if (isfinite(gpsdata->dop.hdop) != 0)
	(void)fprintf(logfile,"    <hdop>%.1f</hdop>\n", gpsdata->dop.hdop);
    if (isfinite(gpsdata->dop.vdop) != 0)
	(void)fprintf(logfile,"    <vdop>%.1f</vdop>\n", gpsdata->dop.vdop);
    if (isfinite(gpsdata->dop.pdop) != 0)
	(void)fprintf(logfile,"    <pdop>%.1f</pdop>\n", gpsdata->dop.pdop);

    (void)fprintf(logfile,"   </trkpt>\n");
    (void)fflush(logfile);
}

static void conditionally_log_fix(struct gps_data_t *gpsdata)
{
    static timespec_t ts_time, old_ts_time, ts_diff;
    static double old_lat, old_lon;
    static bool first = true;

    ts_time = gpsdata->fix.time;
    if (TS_EQ(&ts_time, &old_ts_time) || gpsdata->fix.mode < MODE_2D)
	return;

    /* may not be worth logging if we've moved only a very short distance */
    if (0 < minmove && !first && earth_distance(
					gpsdata->fix.latitude,
					gpsdata->fix.longitude,
					old_lat, old_lon) < minmove)
	return;

    /*
     * Make new track if the jump in time is above
     * timeout.  Handle jumps both forward and
     * backwards in time.  The clock sometimes jumps
     * backward when gpsd is submitting junk on the
     * dbus.
     */
    TS_SUB(&ts_diff, &ts_time, &old_ts_time);
    if (labs((long)ts_diff.tv_sec) > timeout && !first) {
	print_gpx_trk_end();
	intrack = false;
    }

    if (!intrack) {
	print_gpx_trk_start();
	intrack = true;
	if (first)
	    first = false;
    }

    old_ts_time = ts_time;
    if (0 < minmove) {
	old_lat = gpsdata->fix.latitude;
	old_lon = gpsdata->fix.longitude;
    }
    print_fix(gpsdata, ts_time);
}

static void quit_handler(int signum)
{
    /* don't clutter the logs on Ctrl-C */
    if (signum != SIGINT)
	syslog(LOG_INFO, "exiting, signal %d received", signum);
    print_gpx_footer();
    (void)gps_close(&gpsdata);
    exit(EXIT_SUCCESS);
}

/**************************************************************************
 *
 * Main sequence
 *
 **************************************************************************/

static void usage(void)
{
    (void)fprintf(stderr,
                  "Usage: %s [-V] [-h] [-l] [-d] [-D debuglevel]"
                  " [-i timeout] [-f filename] [-m minmove]\n"
                  "\t[-r] [-e exportmethod] [server[:port:[device]]]\n\n"
                  "defaults to '%s -i 5 -e %s localhost:2947'\n",
                  progname, progname, export_default()->name);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    int ch;
    bool daemonize = false;
    bool reconnect = false;
    unsigned int flags = WATCH_ENABLE;
    struct exportmethod_t *method = NULL;

    progname = argv[0];

    method = export_default();
    if (method == NULL) {
	(void)fprintf(stderr, "%s: no export methods.\n", progname);
	exit(EXIT_FAILURE);
    }

    logfile = stdout;
    while ((ch = getopt(argc, argv, "dD:e:f:hi:lm:rV")) != -1) {
	switch (ch) {
	case 'd':
	    openlog(basename(progname), LOG_PID | LOG_PERROR, LOG_DAEMON);
	    daemonize = true;
	    break;
#ifdef CLIENTDEBUG_ENABLE
	case 'D':
	    debug = atoi(optarg);
	    gps_enable_debug(debug, logfile);
	    break;
#endif /* CLIENTDEBUG_ENABLE */
	case 'e':
	    method = export_lookup(optarg);
	    if (method == NULL) {
		(void)fprintf(stderr,
			      "%s: %s is not a known export method.\n",
			      progname, optarg);
		exit(EXIT_FAILURE);
	    }
	    break;
       case 'f':       /* Output file name. */
            {
                char   *fname = NULL;
                time_t  t;
                size_t  s = 0;
                size_t fnamesize = strlen(optarg) + 1;

                t = time(NULL);
                while (s == 0) {
		    char *newfname = realloc(fname, fnamesize);
		    if (newfname == NULL) {
			syslog(LOG_ERR, "realloc failed.");
			goto bailout;
		    } else {
			fname = newfname;
		    }
		    s = strftime(fname, fnamesize-1, optarg, localtime(&t));
		    if (!s) {
                        /* expanded filename did not fit in string, try 
                         * a bigger string */
			fnamesize += 1024;
                    }
                }
                fname[s] = '\0';;
                logfile = fopen(fname, "w");
                if (logfile == NULL) {
		    syslog(LOG_ERR,
			   "Failed to open %s: %s, logging to stdout.",
			   fname, strerror(errno));
		    logfile = stdout;
		}
	    bailout:
                free(fname);
                break;
            }
	case 'i':		/* set polling interval */
	    timeout = (time_t) atoi(optarg);
	    if (timeout < 1)
		timeout = 1;
	    if (timeout >= 3600)
		(void)fprintf(stderr,
		              "WARNING: track timeout is an hour or more!\n");
	    break;
	case 'l':
	    export_list(stderr);
	    exit(EXIT_SUCCESS);
        case 'm':
	    minmove = (double )atoi(optarg);
	    break;
        case 'r':
	    reconnect = true;
	    break;
	case 'V':
	    (void)fprintf(stderr, "%s: version %s (revision %s)\n",
			  progname, VERSION, REVISION);
	    exit(EXIT_SUCCESS);
	default:
	    usage();
	    /* NOTREACHED */
	}
    }

    if (daemonize && logfile == stdout) {
	syslog(LOG_ERR, "Daemon mode with no valid logfile name - exiting.");
	exit(EXIT_FAILURE);
    }

    if (method->magic != NULL) {
	source.server = (char *)method->magic;
	source.port = NULL;
	source.device = NULL;
    } else {
	source.server = (char *)"localhost";
	source.port = (char *)DEFAULT_GPSD_PORT;
	source.device = NULL;
    }

    if (optind < argc) {
	/* in this case, switch to the method "socket" always */
	gpsd_source_spec(argv[optind], &source);
    }
#if 0
    (void)fprintf(logfile,"<!-- server: %s port: %s  device: %s -->\n",
		 source.server, source.port, source.device);
#endif

    /* catch all interesting signals */
    (void)signal(SIGTERM, quit_handler);
    (void)signal(SIGQUIT, quit_handler);
    (void)signal(SIGINT, quit_handler);

    /* might be time to daemonize */
    if (daemonize) {
	/* not SuS/POSIX portable, but we have our own fallback version */
	if (os_daemon(0, 0) != 0)
	    (void) fprintf(stderr,"daemonization failed: %s\n", strerror(errno));
    }

    //syslog (LOG_INFO, "---------- STARTED ----------");

    if (gps_open(source.server, source.port, &gpsdata) != 0) {
	(void)fprintf(stderr,
		      "%s: no gpsd running or network error: %d, %s\n",
		      progname, errno, gps_errstr(errno));
	exit(EXIT_FAILURE);
    }

    if (source.device != NULL)
	flags |= WATCH_DEVICE;
    (void)gps_stream(&gpsdata, flags, source.device);

    print_gpx_header();

    while (gps_mainloop(&gpsdata, timeout * 1000000, conditionally_log_fix) < 0 &&
	   reconnect) {
	/* avoid busy-calling gps_mainloop() */
	(void)sleep(timeout);
	syslog(LOG_INFO, "timeout; about to reconnect");
    }

    print_gpx_footer();
    (void)gps_close(&gpsdata);

    exit(EXIT_SUCCESS);
}
