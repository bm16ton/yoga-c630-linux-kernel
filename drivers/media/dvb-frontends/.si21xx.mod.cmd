cmd_drivers/media/dvb-frontends/si21xx.mod := printf '%s\n'   si21xx.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/si21xx.mod
