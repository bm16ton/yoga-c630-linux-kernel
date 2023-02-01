cmd_drivers/media/dvb-frontends/itd1000.mod := printf '%s\n'   itd1000.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/itd1000.mod
