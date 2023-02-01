cmd_drivers/media/dvb-frontends/or51211.mod := printf '%s\n'   or51211.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/or51211.mod
