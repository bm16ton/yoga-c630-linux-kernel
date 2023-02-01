cmd_drivers/media/dvb-frontends/si2165.mod := printf '%s\n'   si2165.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/si2165.mod
