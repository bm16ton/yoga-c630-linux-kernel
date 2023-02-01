cmd_drivers/media/dvb-frontends/tda10021.mod := printf '%s\n'   tda10021.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/tda10021.mod
