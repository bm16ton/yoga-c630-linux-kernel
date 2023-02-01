cmd_drivers/media/dvb-frontends/tda8261.mod := printf '%s\n'   tda8261.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/tda8261.mod
