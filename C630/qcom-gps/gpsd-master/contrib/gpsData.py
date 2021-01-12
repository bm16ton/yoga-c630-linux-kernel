#! /usr/bin/python
# Written by Dan Mandle http://dan.mandle.me September 2012
# http://www.danmandle.com/blog/getting-gpsd-to-work-with-python/
# License: GPL 2.0

# This code runs compatibly under Python 2 and 3.x for x >= 2.
# Preserve this property!
from __future__ import absolute_import, print_function, division

import gps
import os
import threading
import time

gpsd = None          # setting the global variable

os.system('clear')   # clear the terminal (optional)


class GpsPoller(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        global gpsd                    # bring it in scope
        gpsd = gps.gps(mode=gps.WATCH_ENABLE)  # starting the stream of info
        self.current_value = None
        self.running = True            # setting the thread running to true

    def run(self):
        global gpsd
        while gpsp.running:
            # this will continue to loop and grab EACH set of
            # gpsd info to clear the buffer
            next(gpsd)


if __name__ == '__main__':
    gpsp = GpsPoller()   # create the thread
    try:
        gpsp.start()     # start it up
        while True:
            # It may take a second or two to get good data
            # print(gpsd.fix.latitude,', ',gpsd.fix.longitude,'
            #       Time: ',gpsd.utc

            os.system('clear')

            print()
            print(' GPS reading')
            print('----------------------------------------')
            print('latitude    ', gpsd.fix.latitude)
            print('longitude   ', gpsd.fix.longitude)
            print('time utc    ', gpsd.utc, ' + ', gpsd.fix.time)
            print('altHAE (m)  ', gpsd.fix.altHAE)
            print('eps         ', gpsd.fix.eps)
            print('epx         ', gpsd.fix.epx)
            print('epv         ', gpsd.fix.epv)
            print('ept         ', gpsd.fix.ept)
            print('speed (m/s) ', gpsd.fix.speed)
            print('climb       ', gpsd.fix.climb)
            print('track       ', gpsd.fix.track)
            print('mode        ', gpsd.fix.mode)
            print()
            print("%s satellites in view:" % len(gpsd.satellites))
            for sat in gpsd.satellites:
                print("    %r" % sat)

            time.sleep(5)     # set to whatever

    except (KeyboardInterrupt, SystemExit):
        # when you press ctrl+c
        print("\nKilling Thread...")
        gpsp.running = False
        gpsp.join()   # wait for the thread to finish what it's doing

    print("Done.\nExiting.")
