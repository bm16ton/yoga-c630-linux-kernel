cmd_drivers/media/dvb-frontends/sp2.mod := printf '%s\n'   sp2.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/sp2.mod
