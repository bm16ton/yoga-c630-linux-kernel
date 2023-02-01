cmd_drivers/media/dvb-frontends/ds3000.mod := printf '%s\n'   ds3000.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/ds3000.mod
