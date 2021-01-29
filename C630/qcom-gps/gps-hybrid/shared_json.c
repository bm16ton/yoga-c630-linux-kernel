/****************************************************************************

NAME
   shared_json.c - move data between in-core and JSON structures

DESCRIPTION
   This module uses the generic JSON parser to get data from JSON
representations to gps.h structures. These functions are used in both
the daemon and the client library.

PERMISSIONS
  Written by Eric S. Raymond, 2009
  This file is Copyright (c) 2010 by the GPSD project
  SPDX-License-Identifier: BSD-2-clause

***************************************************************************/

#include <math.h>
#include <stdbool.h>

#include "gpsd.h"
#ifdef SOCKET_EXPORT_ENABLE
#include "gps_json.h"

int json_device_read(const char *buf,
		     struct devconfig_t *dev,
		     const char **endptr)
{
    char tbuf[JSON_DATE_MAX+1];
    /* *INDENT-OFF* */
    const struct json_attr_t json_attrs_device[] = {
	{"class",      t_check,      .dflt.check = "DEVICE"},

        {"path",       t_string,     .addr.string  = dev->path,
	                                .len = sizeof(dev->path)},
	{"activated",  t_string,     .addr.string = tbuf,
			                .len = sizeof(tbuf)},
	{"activated",  t_real,       .addr.real = &dev->activated},
	{"flags",      t_integer,    .addr.integer = &dev->flags},
	{"driver",     t_string,     .addr.string  = dev->driver,
	                                .len = sizeof(dev->driver)},
	{"subtype",    t_string,     .addr.string  = dev->subtype,
	                                .len = sizeof(dev->subtype)},
	{"native",     t_integer,    .addr.integer = &dev->driver_mode,
				        .dflt.integer = DEVDEFAULT_NATIVE},
	{"bps",	       t_uinteger,   .addr.uinteger = &dev->baudrate,
				        .dflt.uinteger = DEVDEFAULT_BPS},
	{"parity",     t_character,  .addr.character = &dev->parity,
                                        .dflt.character = DEVDEFAULT_PARITY},
	{"stopbits",   t_uinteger,   .addr.uinteger = &dev->stopbits,
				        .dflt.uinteger = DEVDEFAULT_STOPBITS},
	{"cycle",      t_real,       .addr.real = &dev->cycle,
				        .dflt.real = NAN},
	{"mincycle",   t_real,       .addr.real = &dev->mincycle,
				        .dflt.real = NAN},
	{NULL},
    };
    /* *INDENT-ON* */
    int status;

    tbuf[0] = '\0';
    status = json_read_object(buf, json_attrs_device, endptr);
    if (status != 0)
	return status;

    if (isnan(dev->activated)!=0) {
	if (tbuf[0] == '\0')
	    dev->activated = NAN;
	else
	    dev->activated = iso8601_to_unix(tbuf);
    }

    return 0;
}

int json_watch_read(const char *buf,
		    struct policy_t *ccp,
		    const char **endptr)
{
    bool dummy_pps_flag;
    /* *INDENT-OFF* */
    struct json_attr_t chanconfig_attrs[] = {
	{"class",          t_check,    .dflt.check = "WATCH"},

	{"enable",         t_boolean,  .addr.boolean = &ccp->watcher,
                                          .dflt.boolean = true},
	{"json",           t_boolean,  .addr.boolean = &ccp->json,
                                          .nodefault = true},
	{"raw",	           t_integer,  .addr.integer = &ccp->raw,
	                                  .nodefault = true},
	{"nmea",	   t_boolean,  .addr.boolean = &ccp->nmea,
	                                  .nodefault = true},
	{"scaled",         t_boolean,  .addr.boolean = &ccp->scaled},
	{"timing",         t_boolean,  .addr.boolean = &ccp->timing},
	{"split24",        t_boolean,  .addr.boolean = &ccp->split24},
	{"pps",            t_boolean,  .addr.boolean = &ccp->pps},
	{"device",         t_string,   .addr.string = ccp->devpath,
	                                  .len = sizeof(ccp->devpath)},
	{"remote",         t_string,   .addr.string = ccp->remote,
	                                  .len = sizeof(ccp->remote)},
	{"pps",            t_boolean,  .addr.boolean = &dummy_pps_flag,
                                          .nodefault = false},
	{NULL},
    };
    /* *INDENT-ON* */
    int status;

    status = json_read_object(buf, chanconfig_attrs, endptr);
    return status;
}

#endif /* SOCKET_EXPORT_ENABLE */

/* shared_json.c ends here */
