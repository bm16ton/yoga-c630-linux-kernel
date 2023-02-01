cmd_drivers/media/dvb-frontends/isl6423.mod := printf '%s\n'   isl6423.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/isl6423.mod
