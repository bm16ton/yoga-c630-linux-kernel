cmd_drivers/media/dvb-frontends/stv6110x.mod := printf '%s\n'   stv6110x.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/stv6110x.mod
