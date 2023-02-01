cmd_drivers/media/dvb-frontends/stv6110.mod := printf '%s\n'   stv6110.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/stv6110.mod
