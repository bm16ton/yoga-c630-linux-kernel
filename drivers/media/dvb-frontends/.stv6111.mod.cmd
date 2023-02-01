cmd_drivers/media/dvb-frontends/stv6111.mod := printf '%s\n'   stv6111.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/stv6111.mod
