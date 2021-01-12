/*
 * This file is Copyright (c) 2010-2018 by the GPSD project
 * SPDX-License-Identifier: BSD-2-clause
 */

#include "gpsd_config.h"  /* must be before all includes */

#include "gpsd.h"
#include "bits.h"
#include "gpsmon.h"

#ifdef SUPERSTAR2_ENABLE
#include "driver_superstar2.h"
extern const struct gps_type_t driver_superstar2;
static WINDOW *satwin;

static bool superstar2_initialize(void)
{
    int i;

    /* "heavily inspired" by monitor_nmea.c */
    if ((satwin = derwin(devicewin, 15, 27, 7, 0)) == NULL)
	return false;
    (void)wborder(satwin, 0, 0, 0, 0, 0, 0, 0, 0), (void)syncok(satwin, true);
    (void)wattrset(satwin, A_BOLD);
    (void)mvwprintw(satwin, 1, 1, "Ch PRN  Az El S/N Fl U");
    for (i = 0; i < 12; i++)
	(void)mvwprintw(satwin, (int)(i + 2), 1, "%2d", i);
    (void)mvwprintw(satwin, 14, 1, " Satellite Data & Status ");
    (void)wattrset(satwin, A_NORMAL);

    return true;
}

static void display_superstar2_svinfo(unsigned char *buf, size_t data_len)
{
    int i;

    if (data_len != 67)
	return;

    for (i = 0; i < 12; i++) {
	/* get info for one channel/satellite */
	int off = i * 5 + 5;
	unsigned char fl, porn, ss;
	char el;
	unsigned short az;

	if ((porn = (unsigned char)getub(buf, off) & 0x1f) == 0)
	    porn = ((unsigned char)getub(buf, off + 3) >> 1) + 87;

	ss = (unsigned char)getub(buf, off + 4);
	el = (char)getsb(buf, off + 1);
	az = (unsigned short)(getub(buf, off + 2) +
			      ((getub(buf, off + 3) & 0x1) << 1));
	fl = (unsigned char)getub(buf, off) & 0xe0;
	(void)wmove(satwin, i + 2, 4);
	(void)wprintw(satwin, "%3u %3d %2d  %02d %02x %c",
		      porn, az, el, ss, fl,
		      ((fl & 0x60) == 0x60) ? 'Y' : ' ');
    }
    (void)wnoutrefresh(satwin);
    return;
}

static void superstar2_update(void)
{
    unsigned char *buf;
    size_t len;
    unsigned char type;

    buf = session.lexer.outbuffer;
    len = session.lexer.outbuflen;
    type = buf[SUPERSTAR2_TYPE_OFFSET];
    switch (type) {
    case SUPERSTAR2_SVINFO:
	display_superstar2_svinfo(buf, len - 3);
	break;
    default:
	break;
    }
}

static int superstar2_command(char line[]UNUSED)
{
    return COMMAND_UNKNOWN;
}

static void superstar2_wrap(void)
{
}

const struct monitor_object_t superstar2_mmt = {
    .initialize = superstar2_initialize,
    .update = superstar2_update,
    .command = superstar2_command,
    .wrap = superstar2_wrap,
    .min_y = 23,.min_x = 80,	/* size of the device window */
    .driver = &driver_superstar2,
};
#endif
