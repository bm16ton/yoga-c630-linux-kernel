cmd_drivers/media/dvb-frontends/mn88473.mod := printf '%s\n'   mn88473.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/mn88473.mod
