cmd_drivers/media/dvb-frontends/s921.mod := printf '%s\n'   s921.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/s921.mod
