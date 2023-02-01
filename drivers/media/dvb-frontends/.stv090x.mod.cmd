cmd_drivers/media/dvb-frontends/stv090x.mod := printf '%s\n'   stv090x.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/stv090x.mod
