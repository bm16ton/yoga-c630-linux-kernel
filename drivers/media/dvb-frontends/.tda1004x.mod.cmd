cmd_drivers/media/dvb-frontends/tda1004x.mod := printf '%s\n'   tda1004x.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/tda1004x.mod
