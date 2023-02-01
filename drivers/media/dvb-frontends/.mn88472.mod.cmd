cmd_drivers/media/dvb-frontends/mn88472.mod := printf '%s\n'   mn88472.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/mn88472.mod
