cmd_drivers/media/dvb-frontends/ts2020.mod := printf '%s\n'   ts2020.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/ts2020.mod
