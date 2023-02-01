cmd_drivers/media/dvb-frontends/ec100.mod := printf '%s\n'   ec100.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/ec100.mod
