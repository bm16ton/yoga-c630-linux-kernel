cmd_drivers/media/dvb-frontends/stv0367.mod := printf '%s\n'   stv0367.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/stv0367.mod
