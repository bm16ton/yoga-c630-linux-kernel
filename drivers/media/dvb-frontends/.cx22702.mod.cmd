cmd_drivers/media/dvb-frontends/cx22702.mod := printf '%s\n'   cx22702.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/cx22702.mod
