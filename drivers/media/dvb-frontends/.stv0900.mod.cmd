cmd_drivers/media/dvb-frontends/stv0900.mod := printf '%s\n'   stv0900_core.o stv0900_sw.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/stv0900.mod
