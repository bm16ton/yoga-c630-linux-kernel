cmd_drivers/media/dvb-frontends/m88ds3103.mod := printf '%s\n'   m88ds3103.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/m88ds3103.mod
