/* test driver for the ECEF to WGS84 conversions in geoid.c
 *
 * This file is Copyright (c) 2010 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "gpsd.h"

int main(int argc, char **argv)
{
    double lat, lon;

    if (argc != 3) {
	(void)fprintf(stderr, "Usage: %s lat lon\n", argv[0]);
	return 1;
    }

    lat = atof(argv[1]);
    lon = atof(argv[2]);

    if (lon > 180.0 || lat < -180.0) {
	(void)fprintf(stderr, " -180 <= lon=%s(%.f) <= 180 ?\n", argv[2], lon);
	return 1;
    }

    if (lat > 90.0 || lat < -90.0) {
	(void)fprintf(stderr, " -90 <= lat=%s(%.f) <= 90 ?\n", argv[1], lat);
	return 1;
    }

    (void)printf(" lat= %f lon= %f geoid correction= %f\n",
                 lat, lon, wgs84_separation(lat, lon));

    return 0;
}
