#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''gps.py -- Python interface to GPSD.

This interface has a lot of historical cruft in it related to old
protocol, and was modeled on the C interface. It won't be thrown
away, but it's likely to be deprecated in favor of something more
Pythonic.

The JSON parts of this (which will be reused by any new interface)
now live in a different module.
'''

#
# This file is Copyright (c) 2010-2019 by the GPSD project
# BSD terms apply: see the file COPYING in the distribution root for details.
#

# This code runs compatibly under Python 2 and 3.x for x >= 2.
# Preserve this property!
from __future__ import absolute_import, print_function, division

from .client import *
from .watch_options import *


NaN = float('nan')


def isfinite(f):
    "Check if f is finite"
    # Python 2 does not think +Inf or -Inf are NaN
    # Python 2 has no easier way to test for Inf
    return float('-inf') < float(f) < float('inf')


# Don't hand-hack this list, it's generated.
ONLINE_SET = (1 << 1)
TIME_SET = (1 << 2)
TIMERR_SET = (1 << 3)
LATLON_SET = (1 << 4)
ALTITUDE_SET = (1 << 5)
SPEED_SET = (1 << 6)
TRACK_SET = (1 << 7)
CLIMB_SET = (1 << 8)
STATUS_SET = (1 << 9)
MODE_SET = (1 << 10)
DOP_SET = (1 << 11)
HERR_SET = (1 << 12)
VERR_SET = (1 << 13)
ATTITUDE_SET = (1 << 14)
SATELLITE_SET = (1 << 15)
SPEEDERR_SET = (1 << 16)
TRACKERR_SET = (1 << 17)
CLIMBERR_SET = (1 << 18)
DEVICE_SET = (1 << 19)
DEVICELIST_SET = (1 << 20)
DEVICEID_SET = (1 << 21)
RTCM2_SET = (1 << 22)
RTCM3_SET = (1 << 23)
AIS_SET = (1 << 24)
PACKET_SET = (1 << 25)
SUBFRAME_SET = (1 << 26)
GST_SET = (1 << 27)
VERSION_SET = (1 << 28)
POLICY_SET = (1 << 29)
LOGMESSAGE_SET = (1 << 30)
ERROR_SET = (1 << 31)
TIMEDRIFT_SET = (1 << 32)
EOF_SET = (1 << 33)
SET_HIGH_BIT = 34
UNION_SET = (RTCM2_SET | RTCM3_SET | SUBFRAME_SET | AIS_SET | VERSION_SET |
             DEVICELIST_SET | ERROR_SET | GST_SET)
STATUS_NO_FIX = 0
STATUS_FIX = 1
STATUS_DGPS_FIX = 2
STATUS_RTK_FIX = 3
STATUS_RTK_FLT = 4
STATUS_DR = 5
STATUS_GNSSDR = 6
STATUS_TIME = 7
STATUS_SIM = 8
STATUS_PPS_FIX = 9
MODE_NO_FIX = 1
MODE_2D = 2
MODE_3D = 3
MAXCHANNELS = 72  # Copied from gps.h, but not required to match
SIGNAL_STRENGTH_UNKNOWN = NaN


class gpsfix(object):
    "Class to hold one GPS fix"

    def __init__(self):
        "Init class gpsfix"

        self.altitude = NaN         # Meters DEPRECATED
        self.altHAE = NaN           # Meters
        self.altMSL = NaN           # Meters
        self.climb = NaN            # Meters per second
        self.datum = ""
        self.dgpsAge = -1
        self.dgpsSta = ""
        self.depth = NaN
        self.device = ""
        self.ecefx = NaN
        self.ecefy = NaN
        self.ecefz = NaN
        self.ecefvx = NaN
        self.ecefvy = NaN
        self.ecefvz = NaN
        self.ecefpAcc = NaN
        self.ecefvAcc = NaN
        self.epc = NaN
        self.epd = NaN
        self.eph = NaN
        self.eps = NaN
        self.ept = NaN
        self.epv = NaN
        self.epx = NaN
        self.epy = NaN
        self.geoidSep = NaN        # Meters
        self.latitude = self.longitude = 0.0
        self.magtrack = NaN
        self.magvar = NaN
        self.mode = MODE_NO_FIX
        self.relN = NaN
        self.relE = NaN
        self.relD = NaN
        self.sep = NaN              # a.k.a. epe
        self.speed = NaN            # Knots
        self.status = STATUS_NO_FIX
        self.time = NaN
        self.track = NaN            # Degrees from true north
        self.velN = NaN
        self.velE = NaN
        self.velD = NaN


class gpsdata(object):
    "Position, track, velocity and status information returned by a GPS."

    class satellite(object):
        "Class to hold satellite data"
        def __init__(self, PRN, elevation, azimuth, ss, used=None):
            self.PRN = PRN
            self.elevation = elevation
            self.azimuth = azimuth
            self.ss = ss
            self.used = used

        def __repr__(self):
            return "PRN: %3d  E: %3d  Az: %3d  Ss: %3d  Used: %s" % (
                self.PRN, self.elevation, self.azimuth, self.ss,
                "ny"[self.used])

    def __init__(self):
        # Initialize all data members
        self.online = 0                 # NZ if GPS on, zero if not

        self.valid = 0
        self.fix = gpsfix()

        self.status = STATUS_NO_FIX
        self.utc = ""

        self.satellites_used = 0        # Satellites used in last fix
        self.xdop = self.ydop = self.vdop = self.tdop = 0
        self.pdop = self.hdop = self.gdop = 0.0

        self.epe = 0.0

        self.satellites = []            # satellite objects in view

        self.gps_id = None
        self.driver_mode = 0
        self.baudrate = 0
        self.stopbits = 0
        self.cycle = 0
        self.mincycle = 0
        self.device = None
        self.devices = []

        self.version = None

    def __repr__(self):
        st = "Time:     %s (%s)\n" % (self.utc, self.fix.time)
        st += "Lat/Lon:  %f %f\n" % (self.fix.latitude, self.fix.longitude)
        if not isfinite(self.fix.altHAE):
            st += "Altitude HAE: ?\n"
        else:
            st += "Altitude HAE: %f\n" % (self.fix.altHAE)
        if not isfinite(self.fix.speed):
            st += "Speed:    ?\n"
        else:
            st += "Speed:    %f\n" % (self.fix.speed)
        if not isfinite(self.fix.track):
            st += "Track:    ?\n"
        else:
            st += "Track:    %f\n" % (self.fix.track)
        st += "Status:   STATUS_%s\n" \
              % ("NO_FIX", "FIX", "DGPS_FIX")[self.status]
        st += "Mode:     MODE_%s\n" \
              % ("ZERO", "NO_FIX", "2D", "3D")[self.fix.mode]
        st += "Quality:  %d p=%2.2f h=%2.2f v=%2.2f t=%2.2f g=%2.2f\n" % \
              (self.satellites_used, self.pdop, self.hdop, self.vdop,
               self.tdop, self.gdop)
        st += "Y: %s satellites in view:\n" % len(self.satellites)
        for sat in self.satellites:
            st += "    %r\n" % sat
        return st


class gps(gpscommon, gpsdata, gpsjson):
    "Client interface to a running gpsd instance."

    # module version, would be nice to automate the version
    __version__ = "3.20"

    def __init__(self, host="127.0.0.1", port=GPSD_PORT, verbose=0, mode=0,
                 reconnect=False):
        self.activated = None
        self.clock_sec = NaN
        self.clock_nsec = NaN
        self.path = ''
        self.precision = 0
        self.real_sec = NaN
        self.real_nsec = NaN
        self.serialmode = "8N1"
        gpscommon.__init__(self, host, port, verbose, reconnect)
        gpsdata.__init__(self)
        gpsjson.__init__(self)
        if mode:
            self.stream(mode)

    def _oldstyle_shim(self):
        # The rest is backwards compatibility for the old interface
        def default(k, dflt, vbit=0):
            "Return default for key"
            if k not in self.data.keys():
                return dflt

            self.valid |= vbit
            return self.data[k]

        if self.data.get("class") == "VERSION":
            self.version = self.data
        elif self.data.get("class") == "DEVICE":
            self.valid = ONLINE_SET | DEVICE_SET
            self.path = self.data["path"]
            self.activated = default("activated", None)
            driver = default("driver", None, DEVICEID_SET)
            subtype = default("subtype", None, DEVICEID_SET)
            self.gps_id = driver
            if subtype:
                self.gps_id += " " + subtype
            self.baudrate = default("bps", 0)
            self.cycle = default("cycle", NaN)
            self.driver_mode = default("native", 0)
            self.mincycle = default("mincycle", NaN)
            self.serialmode = default("serialmode", "8N1")
        elif self.data.get("class") == "TPV":
            self.device = default("device", "missing")
            self.utc = default("time", None, TIME_SET)
            self.valid = ONLINE_SET
            if self.utc is not None:
                # self.utc is always iso 8601 string
                # just copy to fix.time
                self.fix.time = self.utc
            self.fix.altitude = default("alt", NaN, ALTITUDE_SET)  # DEPRECATED
            self.fix.altHAE = default("altHAE", NaN, ALTITUDE_SET)
            self.fix.altMSL = default("altMSL", NaN, ALTITUDE_SET)
            self.fix.climb = default("climb", NaN, CLIMB_SET)
            self.fix.epc = default("epc", NaN, CLIMBERR_SET)
            self.fix.epd = default("epd", NaN)
            self.fix.eps = default("eps", NaN, SPEEDERR_SET)
            self.fix.ept = default("ept", NaN, TIMERR_SET)
            self.fix.epv = default("epv", NaN, VERR_SET)
            self.fix.epx = default("epx", NaN, HERR_SET)
            self.fix.epy = default("epy", NaN, HERR_SET)
            self.fix.latitude = default("lat", NaN, LATLON_SET)
            self.fix.longitude = default("lon", NaN)
            self.fix.mode = default("mode", 0, MODE_SET)
            self.fix.speed = default("speed", NaN, SPEED_SET)
            self.fix.status = default("status", 1)
            self.fix.track = default("track", NaN, TRACK_SET)
        elif self.data.get("class") == "SKY":
            self.device = default("device", "missing")
            for attrp in ("g", "h", "p", "t", "v", "x", "y"):
                n = attrp + "dop"
                setattr(self, n, default(n, NaN, DOP_SET))
            if "satellites" in self.data.keys():
                self.satellites = []
                for sat in self.data['satellites']:
                    if 'el' not in sat:
                        sat['el'] = -999
                    if 'az' not in sat:
                        sat['az'] = -999
                    if 'ss' not in sat:
                        sat['ss'] = -999
                    self.satellites.append(gps.satellite(PRN=sat['PRN'],
                                           elevation=sat['el'],
                                           azimuth=sat['az'], ss=sat['ss'],
                                           used=sat['used']))
            self.satellites_used = 0
            for sat in self.satellites:
                if sat.used:
                    self.satellites_used += 1
            self.valid = ONLINE_SET | SATELLITE_SET
        elif self.data.get("class") == "PPS":
            self.device = default("device", "missing")
            self.real_sec = default("real_sec", NaN)
            self.real_nsec = default("real_nsec", NaN)
            self.clock_sec = default("clock_sec", NaN)
            self.clock_nsec = default("clock_nsec", NaN)
            self.precision = default("precision", 0)
        # elif self.data.get("class") == "DEVICES":
        # TODO: handle class DEVICES    # pylint: disable=fixme

    def read(self):
        "Read and interpret data from the daemon."
        status = gpscommon.read(self)
        if status <= 0:
            return status
        if self.response.startswith("{") and self.response.endswith("}\r\n"):
            self.unpack(self.response)
            self._oldstyle_shim()
            self.valid |= PACKET_SET
        return 0

    def __next__(self):
        "Python 3 version of next()."
        if self.read() == -1:
            raise StopIteration
        if hasattr(self, "data"):
            return self.data

        return self.response

    def next(self):
        "Python 2 backward compatibility."
        return self.__next__()

    def stream(self, flags=0, devpath=None):
        "Ask gpsd to stream reports at your client."

        gpsjson.stream(self, flags, devpath)


def is_sbas(prn):
    "Is this the NMEA ID of an SBAS satellite?"
    return 120 <= prn <= 158


if __name__ == '__main__':
    import getopt
    import sys
    (options, arguments) = getopt.getopt(sys.argv[1:], "v")
    streaming = False
    verbose = False
    for (switch, val) in options:
        if switch == '-v':
            verbose = True
    if len(arguments) > 2:
        print('Usage: gps.py [-v] [host [port]]')
        sys.exit(1)

    opts = {"verbose": verbose}
    if arguments:
        opts["host"] = arguments[0]
    if arguments:
        opts["port"] = arguments[1]

    session = gps(**opts)
    session.stream(WATCH_ENABLE)
    try:
        for report in session:
            print(report)
    except KeyboardInterrupt:
        # Avoid garble on ^C
        print("")

# gps.py ends here
