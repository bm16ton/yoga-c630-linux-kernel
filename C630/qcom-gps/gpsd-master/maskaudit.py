#!/usr/bin/env python
#
# This file is Copyright (c) 2010 by the GPSD project
# SPDX-License-Identifier: BSD-2-clause
#
# With -p, dump a Python status mask list translated from the C one.
#
# With -c, generate C code to dump masks for debugging purposes.
#
# With -t, tabulate usage of defines to find unused ones.  Requires -c or -d.

# This code runs compatibly under Python 2 and 3.x for x >= 2.
# Preserve this property!
from __future__ import absolute_import, print_function, division

import getopt
import glob
import sys

try:
    from subprocess import getstatusoutput
except ImportError:
    from commands import getstatusoutput


class SourceExtractor(object):
    def __init__(self, sourcefile, clientside):
        self.sourcefile = sourcefile
        self.clientside = clientside
        self.daemonfiles = [
            "gpsd.c",
            "libgpsd_core.c",
            "pseudonmea.c",
            "drivers.c",
            "gpsmon.c",
            "subframe.c"
        ] + glob.glob("driver_*.c") + glob.glob("monitor_*.c")
        self.masks = []
        self.primitive_masks = []
        for line in open(self.sourcefile):
            if (((line.startswith("#define") and
                 ("_SET" in line or "_IS" in line)))):
                fields = line.split()
                self.masks.append((fields[1], fields[2]))
                if ((fields[2].startswith("(1llu<<") or
                     fields[2].startswith("INTERNAL_SET"))):
                    self.primitive_masks.append((fields[1], fields[2]))

    def in_library(self, flag):
        (status, _output) = getstatusoutput(
            "grep '%s' libgps_core.c libgps_json.c gpsctl.c" % flag)
        return status == 0

    def in_daemon(self, flag):
        (status, _output) = getstatusoutput(
            "grep '%s' %s" % (flag, " ".join(self.daemonfiles)))
        return status == 0

    def relevant(self, flag):
        if self.clientside:
            return self.in_library(flag)

        return self.in_daemon(flag)


if __name__ == '__main__':
    try:
        (options, arguments) = getopt.getopt(sys.argv[1:], "cdpt")
        pythonize = tabulate = False
        clientgen = daemongen = False
        for (switch, val) in options:
            if switch == '-p':
                pythonize = True
            if switch == '-c':
                clientgen = True
            if switch == '-d':
                daemongen = True
            if switch == '-t':
                tabulate = True

        if not arguments:
            srcdir = '.'
        else:
            srcdir = arguments[0]

        clientside = SourceExtractor(srcdir + "/gps.h", clientside=True)
        daemonside = SourceExtractor(srcdir + "/gpsd.h", clientside=False)
        if clientgen:
            source = clientside
            banner = "Library"
        elif daemongen:
            source = daemonside
            banner = "Daemon"
        else:
            sys.stderr.write("maskaudit: need -c or -d option\n")
            sys.exit(1)

        if tabulate:
            print("%-14s	%8s" % (" ", banner))
            for (flag, value) in source.masks:
                print("%-14s	%8s" % (flag, source.relevant(flag)))
        if pythonize:
            for (d, v) in source.masks:
                if v[-1] == 'u':
                    v = v[:-1]
                print("%-15s\t= %s" % (d, v))
        if not pythonize and not tabulate:
            maxout = 0
            for (d, v) in source.primitive_masks:
                if source.relevant(d):
                    stem = d
                    if stem.endswith("_SET"):
                        stem = stem[:-4]
                    if stem.endswith("_IS"):
                        stem = stem[:-3]
                    maxout += len(stem) + 1
            print("""/* This code is generated.  Do not hand-hack it! */

/*
 * Also, beware that it is something of a CPU hog when called on every packet.
 * Try to write guards so it is only called at higher log levels.
 */

#include \"gpsd_config.h\"  /* must be before all includes */

#include <stdio.h>
#include <string.h>

#include \"gpsd.h\"

const char *gps_maskdump(gps_mask_t set)
{
    static char buf[%d];
    const struct {
        gps_mask_t      mask;
        const char      *name;
    } *sp, names[] = {""" % (maxout + 3,))
            masks = clientside.primitive_masks + daemonside.primitive_masks
            for (flag, value) in masks:
                stem = flag
                if stem.endswith("_SET"):
                    stem = stem[:-4]
                if stem.endswith("_IS"):
                    stem = stem[:-3]
                print("        {%s,\t\"%s\"}," % (flag, stem))
            print('''\
    };

    memset(buf, '\\0', sizeof(buf));
    buf[0] = '{';
    for (sp = names; sp < names + sizeof(names)/sizeof(names[0]); sp++)
        if ((set & sp->mask)!=0) {
            (void)strlcat(buf, sp->name, sizeof(buf));
            (void)strlcat(buf, "|", sizeof(buf));
        }
    if (buf[1] != \'\\0\')
        buf[strlen(buf)-1] = \'\\0\';
    (void)strlcat(buf, "}", sizeof(buf));
    return buf;
}
''')
    except KeyboardInterrupt:
        pass

# The following sets edit modes for GNU EMACS
# Local Variables:
# mode:python
# End:
