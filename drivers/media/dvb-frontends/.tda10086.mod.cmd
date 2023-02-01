cmd_drivers/media/dvb-frontends/tda10086.mod := printf '%s\n'   tda10086.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/tda10086.mod
