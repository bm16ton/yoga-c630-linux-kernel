cmd_drivers/media/dvb-frontends/sp887x.mod := printf '%s\n'   sp887x.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/sp887x.mod
