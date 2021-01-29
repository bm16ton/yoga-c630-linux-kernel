#!/usr/bin/env python
#
# This is a valgrind torture test for the gpsd daemon.
# It's not really expected to spot anything as long as we aren't using
# malloc and friends in the daemon.
#
# This file is Copyright (c) 2010 by the GPSD project
# SPDX-License-Identifier: BSD-2-clause
#
# This code runs compatibly under Python 2 and 3.x for x >= 2.
# Preserve this property!
from __future__ import absolute_import, print_function, division

import sys

import gps.fake

debuglevel = 1

invocation = "valgrind --tool=memcheck --gen-suppressions=yes " \
             "--leak-check=yes --suppressions=valgrind-suppressions"
test = gps.fake.TestSession(prefix=invocation, options="-D %d" % debuglevel)
test.progress = sys.stderr.write

try:
    test.spawn()
    print("\n*** Test #1: Normal single-client-session behavior.")
    print("**** Add a GPS.\n")
    gps1 = test.gps_add("test/daemon/bu303-moving.log")

    print("\n**** Add and remove a client.\n")
    c1 = test.client_add("w\n")
    test.gather(3)
    test.client_remove(c1)

    print("\n**** Remove the GPS.")
    test.gps_remove(gps1)
    print("*** Test #1 complete.\n")
    test.wait(3)

    ######################################################################

    print("\n*** Test #2: Successive non-overlapping client sessions.")
    print("**** Add a GPS.\n")
    gps1 = test.gps_add("test/daemon/bu303-climbing.log")

    print("\n**** Add and remove first client.\n")
    c1 = test.client_add("w\n")
    test.gather(3)
    test.client_remove(c1)
    test.wait(3)

    print("\n**** Add and remove second client.\n")
    c2 = test.client_add("w\n")
    test.gather(3)
    test.client_remove(c2)
    test.wait(3)

    print("\n**** Remove the GPS.")
    test.gps_remove(gps1)
    print("*** Test #2 complete.\n")
    test.wait(3)

    ######################################################################

    print("\n*** Test #3: Overlapping client sessions.")
    print("**** Add a GPS.\n")
    gps1 = test.gps_add("test/daemon/bu303-climbing.log")

    print("\n**** Add first client.\n")
    c1 = test.client_add("w\n")
    test.gather(2)
    print("\n**** Add second client.\n")
    c2 = test.client_add("w\n")
    test.gather(3)
    print("\n**** Remove first client.\n")
    test.client_remove(c1)
    test.gather(2)
    print("\n**** Remove second client.\n")
    test.client_remove(c2)

    print("\n**** Remove the GPS.")
    test.gps_remove(gps1)
    print("*** Test #3 complete.\n")

    ######################################################################

    print("\n*** Test #4: GPS removed while client still active.")
    print("**** Add a GPS.\n")
    gps1 = test.gps_add("test/daemon/bu303-moving.log")

    print("\n**** Add a client.\n")
    c1 = test.client_add("w\n")
    test.gather(3)
    print("\n**** Remove the GPS.")
    test.gps_remove(gps1)
    test.wait(3)
    print("\n**** Remove the client.\n")
    test.client_remove(c1)

    print("*** Test #4 complete.\n")
finally:
    test.cleanup()

# The following sets edit modes for GNU EMACS
# Local Variables:
# mode:python
# End:
