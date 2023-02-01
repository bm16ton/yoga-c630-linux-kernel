cmd_drivers/media/dvb-frontends/a8293.mod := printf '%s\n'   a8293.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/a8293.mod
