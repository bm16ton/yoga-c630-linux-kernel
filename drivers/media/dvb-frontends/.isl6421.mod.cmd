cmd_drivers/media/dvb-frontends/isl6421.mod := printf '%s\n'   isl6421.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/isl6421.mod
