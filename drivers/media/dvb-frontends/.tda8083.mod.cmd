cmd_drivers/media/dvb-frontends/tda8083.mod := printf '%s\n'   tda8083.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/tda8083.mod
