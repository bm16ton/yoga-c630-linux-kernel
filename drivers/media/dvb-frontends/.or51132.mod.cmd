cmd_drivers/media/dvb-frontends/or51132.mod := printf '%s\n'   or51132.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/or51132.mod
