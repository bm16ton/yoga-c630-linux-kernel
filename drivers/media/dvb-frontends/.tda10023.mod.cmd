cmd_drivers/media/dvb-frontends/tda10023.mod := printf '%s\n'   tda10023.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/tda10023.mod
