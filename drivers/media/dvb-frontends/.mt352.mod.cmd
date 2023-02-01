cmd_drivers/media/dvb-frontends/mt352.mod := printf '%s\n'   mt352.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/mt352.mod
