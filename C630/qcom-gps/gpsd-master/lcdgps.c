/*
 * Copyright (c) 2005 Jeff Francis <jeff@gritch.org>
 *
 * This file is Copyright (c) 2010-20189 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 *
 */

/*
  Jeff Francis
  jeff@gritch.org

  A client that passes gpsd data to lcdproc, turning your car computer
  into a very expensive feature-free GPS receiver ;^).  Currently
  assumes a 4x40 LCD and writes data formatted to fit that size
  screen.  Also displays Maidenhead grid square output for the hams among us.

  This program assumes that LCDd (lcdproc) is running locally on the
  default (13666) port.  The #defines LCDDHOST and LCDDPORT can be
  changed to talk to a different host and TCP port.
*/

#define LCDDHOST "localhost"
#define LCDDPORT 13666

#define CLIMB 3

#include "gpsd_config.h"  /* must be before all includes */

#include <arpa/inet.h>
#include <errno.h>
#include <math.h>
#include <netdb.h>        /* for gethostbyname() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef AF_UNSPEC
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif /* AF_UNSPEC */
#ifndef INADDR_ANY
#include <netinet/in.h>
#endif /* INADDR_ANY */

#include "gps.h"
#include "gpsdclient.h"
#include "revision.h"
#include "os_compat.h"

/* Prototypes. */
ssize_t sockreadline(int sockd,void *vptr,size_t maxlen);
ssize_t sockwriteline(int sockd,const void *vptr,size_t n);
int send_lcd(char *buf);

static struct fixsource_t source;
static struct gps_data_t gpsdata;
static float altfactor = METERS_TO_FEET;
static float speedfactor = MPS_TO_MPH;
static char *altunits = "ft";
static char *speedunits = "mph";
double avgclimb, climb[CLIMB];

/* Global socket descriptor for LCDd. */
int sd;

/*  Read a line from a socket  */
ssize_t sockreadline(int sockd,void *vptr,size_t maxlen) {
  ssize_t n;
  char    c,*buffer;

  buffer=vptr;

  for (n = 1; n < (ssize_t)maxlen; n++) {
    ssize_t rc;
    if ((rc=read(sockd,&c,1))==1) {
      *buffer++=c;
      if (c=='\n')
        break;
    }
    else if (rc==0) {
      if (n==1)
        return(0);
      else
        break;
    }
    else {
      if (errno==EINTR)
        continue;
      return(-1);
    }
  }

  *buffer=0;
  return(n);
}

/*  Write a line to a socket  */
ssize_t sockwriteline(int sockd,const void *vptr,size_t n) {
  size_t      nleft;
  const char *buffer;

  buffer=vptr;
  nleft=n;

  while (nleft>0) {
    ssize_t     nwritten;
    if ((nwritten= write(sockd,buffer,nleft))<=0) {
      if (errno==EINTR)
        nwritten=0;
      else
        return(-1);
    }
    nleft-=nwritten;
    buffer+=nwritten;
  }

  return(n);
}

/* send a command to the LCD */
int send_lcd(char *buf) {

  int res;
  char rcvbuf[256];
  size_t outlen;

  /* Limit the size of outgoing strings. */
  outlen = strlen(buf);
  if (outlen > 255) {
    outlen = 256;
  }

  /* send the command */
  (void)sockwriteline(sd,buf,outlen);

  /* TODO:  check return status */

  /* read the data */
  res=sockreadline(sd,rcvbuf,sizeof(rcvbuf)-1);

  /* null-terminate the string before printing */
  /* rcvbuf[res-1]=0; FIX-ME: not using this at the moment... */

  /* return the result */
  return(res);
}

/* reset the LCD */
static void reset_lcd(void) {

  /* Initialize.  In theory, we should look at what's returned, as it
     tells us info on the attached LCD module.  TODO. */
  send_lcd("hello\n");

  /* Set up the screen */
  send_lcd("client_set name {GPSD test}\n");
  send_lcd("screen_add gpsd\n");
  send_lcd("widget_add gpsd one string\n");
  send_lcd("widget_add gpsd two string\n");
  send_lcd("widget_add gpsd three string\n");
  send_lcd("widget_add gpsd four string\n");
}

static enum deg_str_type deg_type = deg_dd;

/* This gets called once for each new sentence. */
static void update_lcd(struct gps_data_t *gpsdata)
{
  char tmpbuf[255];
  char *gridsquare;

  /* Get our location in Maidenhead. */
  gridsquare = maidenhead(gpsdata->fix.latitude,gpsdata->fix.longitude);

  /* Fill in the latitude and longitude. */
  if (gpsdata->fix.mode >= MODE_2D) {
    int track;
    char *s;

    s = deg_to_str(deg_type, gpsdata->fix.latitude);
    snprintf(tmpbuf, sizeof(tmpbuf) - 1,
             "widget_set gpsd one 1 1 {Lat: %s %c}\n", s,
             (gpsdata->fix.latitude < 0) ? 'S' : 'N');
    send_lcd(tmpbuf);

    s = deg_to_str(deg_type, gpsdata->fix.longitude);
    snprintf(tmpbuf, sizeof(tmpbuf) - 1,
             "widget_set gpsd two 1 2 {Lon: %s %c}\n", s,
             (gpsdata->fix.longitude < 0) ? 'W' : 'E');
    send_lcd(tmpbuf);

    /* As a pilot, a heading of "0" gives me the heebie-jeebies (ie, 0
       == "invalid heading data", 360 == "North"). */
    track=(int)(gpsdata->fix.track);
    if (track == 0) track = 360;

    snprintf(tmpbuf, sizeof(tmpbuf) - 1,
             "widget_set gpsd three 1 3 {%.1f %s %d deg}\n",
             gpsdata->fix.speed*speedfactor, speedunits,
             track);
    send_lcd(tmpbuf);

  } else {

    send_lcd("widget_set gpsd one 1 1 {Lat: n/a}\n");
    send_lcd("widget_set gpsd two 1 2 {Lon: n/a}\n");
    send_lcd("widget_set gpsd three 1 3 {n/a}\n");
  }

  /* Fill in the altitude and fix status. */
  if (gpsdata->fix.mode == MODE_3D) {
    int n;
    for(n=0;n<CLIMB-2;n++) climb[n]=climb[n+1];
    climb[CLIMB-1]=gpsdata->fix.climb;
    avgclimb=0.0;
    for(n=0;n<CLIMB;n++) avgclimb+=climb[n];
    avgclimb/=CLIMB;
    snprintf(tmpbuf, sizeof(tmpbuf) - 1,
             "widget_set gpsd four 1 4 {%d %s %s %d fpm       }\n",
            (int)(gpsdata->fix.altMSL * altfactor), altunits,
            gridsquare, (int)(avgclimb * METERS_TO_FEET * 60));
  } else {
    snprintf(tmpbuf, sizeof(tmpbuf) - 1, "widget_set gpsd four 1 4 {n/a}\n");
  }
  send_lcd(tmpbuf);
}

static void usage( char *prog)
{
  (void)fprintf(stderr,
        "Usage: %s [OPTIONS] [server[:port:[device]]]\n\n"
        "  -h          Show this help, then exit\n"
        "  -j          Turn on anti-jitter buffering\n"
        "  -l {d|m|s}  Select lat/lon format\n"
        "                d = DD.dddddd (default)\n"
        "                m = DD MM.mmmm'\n"
        "                s = DD MM' SS.sss\"\n"
        "  -s          Sleep for 10 seconds before starting\n"
        "  -u {i|m|m}  Select Units\n"
        "                i = Imperial (default)\n"
        "                n = Nautical\n"
        "                m = Metric\n"
        "  -V          Show version, then exit\n"
        , prog);

  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    int option, rc;
    struct sockaddr_in localAddr, servAddr;
    struct hostent *h;

    int n;
    for(n=0;n<CLIMB;n++) climb[n]=0.0;

    switch (gpsd_units())
    {
    case imperial:
	altfactor = METERS_TO_FEET;
	altunits = "ft";
	speedfactor = MPS_TO_MPH;
	speedunits = "mph";
	break;
    case nautical:
	altfactor = METERS_TO_FEET;
	altunits = "ft";
	speedfactor = MPS_TO_KNOTS;
	speedunits = "knots";
	break;
    case metric:
	altfactor = 1;
	altunits = "m";
	speedfactor = MPS_TO_KPH;
	speedunits = "kph";
	break;
    default:
	/* leave the default alone */
	break;
    }

    /* Process the options.  Print help if requested. */
    while ((option = getopt(argc, argv, "hl:su:V")) != -1) {
	switch (option) {
	case 'h':
	default:
	    usage(argv[0]);
	    break;
	case 'l':
	    switch ( optarg[0] ) {
	    case 'd':
		deg_type = deg_dd;
		continue;
	    case 'm':
		deg_type = deg_ddmm;
		continue;
	    case 's':
		deg_type = deg_ddmmss;
		continue;
	    default:
		(void)fprintf(stderr, "Unknown -l argument: %s\n", optarg);
	    }
	    break;
	case 's':
	    sleep(10);
	    continue;
	case 'u':
	    switch ( optarg[0] ) {
	    case 'i':
		altfactor = METERS_TO_FEET;
		altunits = "ft";
		speedfactor = MPS_TO_MPH;
		speedunits = "mph";
		continue;
	    case 'n':
		altfactor = METERS_TO_FEET;
		altunits = "ft";
		speedfactor = MPS_TO_KNOTS;
		speedunits = "knots";
		continue;
	    case 'm':
		altfactor = 1;
		altunits = "m";
		speedfactor = MPS_TO_KPH;
		speedunits = "kph";
		continue;
	    default:
                break;
	    }
            (void)fprintf(stderr, "Unknown -u argument: %s\n", optarg);
            break;
	case 'V':
	    (void)fprintf(stderr, "lcdgps revision " REVISION "\n");
	    exit(EXIT_SUCCESS);
	}
    }

    /* Grok the server, port, and device. */
  if (optind < argc) {
      gpsd_source_spec(argv[optind], &source);
  } else
      gpsd_source_spec(NULL, &source);

    /* Daemonize... */
  if (os_daemon(0, 0) != 0)
      (void)fprintf(stderr,
		    "lcdgps: daemonization failed: %s\n",
		    strerror(errno));

    /* Open the stream to gpsd. */
    if (gps_open(source.server, source.port, &gpsdata) != 0) {
	(void)fprintf( stderr,
		       "lcdgps: no gpsd running or network error: %d, %s\n",
		       errno, gps_errstr(errno));
	exit(EXIT_FAILURE);
    }

    /* Connect to LCDd */
    h = gethostbyname(LCDDHOST);
    if (h==NULL) {
	printf("%s: unknown host '%s'\n",argv[0],LCDDHOST);
	exit(EXIT_FAILURE);
    }

    servAddr.sin_family = h->h_addrtype;
    memcpy((char *) &servAddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
    servAddr.sin_port = htons(LCDDPORT);

    /* create socket */
    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (BAD_SOCKET(sd)) {
	perror("cannot open socket ");
	exit(EXIT_FAILURE);
    }

    /* bind any port number */
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    localAddr.sin_port = htons(0);

    /* coverity[uninit_use_in_call] */
    rc = bind(sd, (struct sockaddr *) &localAddr, sizeof(localAddr));
    if (rc == -1) {
	printf("%s: cannot bind port TCP %d\n",argv[0],LCDDPORT);
	perror("error ");
	exit(EXIT_FAILURE);
    }

    /* connect to server */
    /* coverity[uninit_use_in_call] */
    rc = connect(sd, (struct sockaddr *) &servAddr, sizeof(servAddr));
    if (rc == -1) {
	perror("cannot connect ");
	exit(EXIT_FAILURE);
    }

    /* Do the initial field label setup. */
    reset_lcd();

    /* Here's where updates go. */
    unsigned int flags = WATCH_ENABLE;
    if (source.device != NULL)
	flags |= WATCH_DEVICE;
    (void)gps_stream(&gpsdata, flags, source.device);

    for (;;) { /* heart of the client */
	if (!gps_waiting(&gpsdata, 50000000)) {
	    (void)fprintf(stderr, "lcdgps: error while waiting\n");
	    exit(EXIT_FAILURE);
	} else {
	    (void)gps_read(&gpsdata, NULL, 0);
	    update_lcd(&gpsdata);
	}

    }
}
