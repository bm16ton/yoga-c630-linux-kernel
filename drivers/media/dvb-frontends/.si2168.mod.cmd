cmd_drivers/media/dvb-frontends/si2168.mod := printf '%s\n'   si2168.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/si2168.mod
