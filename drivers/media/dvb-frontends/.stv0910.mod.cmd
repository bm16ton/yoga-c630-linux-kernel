cmd_drivers/media/dvb-frontends/stv0910.mod := printf '%s\n'   stv0910.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/stv0910.mod
