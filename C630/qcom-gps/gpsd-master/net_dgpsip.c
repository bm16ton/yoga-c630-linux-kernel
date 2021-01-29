/* net_dgpsip.c -- gather and dispatch DGPS data from DGPSIP servers
 *
 * This file is Copyright (c) 2010-2018 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 */

#include "gpsd_config.h"  /* must be before all includes */

#include <sys/types.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

#include "gpsd.h"

int dgpsip_open(struct gps_device_t *device, const char *dgpsserver)
/* open a connection to a DGPSIP server */
{
    char *colon, *dgpsport = "rtcm-sc104";
    int opts;

    device->dgpsip.reported = false;
    if ((colon = strchr(dgpsserver, ':')) != NULL) {
	dgpsport = colon + 1;
	*colon = '\0';
    }
    if (!getservbyname(dgpsport, "tcp"))
	dgpsport = DEFAULT_RTCM_PORT;

    device->gpsdata.gps_fd =
	netlib_connectsock(AF_UNSPEC, dgpsserver, dgpsport, "tcp");
    // cppcheck-suppress pointerPositive
    if (device->gpsdata.gps_fd >= 0) {
	char hn[256], buf[BUFSIZ];
	GPSD_LOG(LOG_PROG, &device->context->errout,
		 "connection to DGPS server %s established.\n",
		 dgpsserver);
	(void)gethostname(hn, sizeof(hn));
	/* greeting required by some RTCM104 servers; others will ignore it */
	(void)snprintf(buf, sizeof(buf), "HELO %s gpsd %s\r\nR\r\n", hn,
		       VERSION);
	if (write(device->gpsdata.gps_fd, buf, strlen(buf)) != (ssize_t) strlen(buf))
	    GPSD_LOG(LOG_ERROR, &device->context->errout,
		     "hello to DGPS server %s failed\n",
		     dgpsserver);
    } else
	GPSD_LOG(LOG_ERROR, &device->context->errout,
		 "can't connect to DGPS server %s, netlib error %d.\n",
		 dgpsserver, device->gpsdata.gps_fd);
    opts = fcntl(device->gpsdata.gps_fd, F_GETFL);

    if (opts >= 0)
	(void)fcntl(device->gpsdata.gps_fd, F_SETFL, opts | O_NONBLOCK);
    device->servicetype = service_dgpsip;
    return device->gpsdata.gps_fd;
}

void dgpsip_report(struct gps_context_t *context,
		   struct gps_device_t *gps,
		   struct gps_device_t *dgpsip)
/* may be time to ship a usage report to the DGPSIP server */
{
    /*
     * 10 is an arbitrary number, the point is to have gotten several good
     * fixes before reporting usage to our DGPSIP server.
     */
    if (context->fixcnt > 10 && !dgpsip->dgpsip.reported) {
	dgpsip->dgpsip.reported = true;
	if (dgpsip->gpsdata.gps_fd > -1) {
	    char buf[BUFSIZ];
	    (void)snprintf(buf, sizeof(buf), "R %0.8f %0.8f %0.2f\r\n",
			   gps->gpsdata.fix.latitude,
			   gps->gpsdata.fix.longitude,
			   gps->gpsdata.fix.altMSL);
	    if (write(dgpsip->gpsdata.gps_fd, buf, strlen(buf)) ==
		(ssize_t) strlen(buf))
		GPSD_LOG(LOG_IO, &context->errout, "=> dgps %s\n", buf);
	    else
		GPSD_LOG(LOG_IO, &context->errout, "write to dgps FAILED\n");
	}
    }
}

