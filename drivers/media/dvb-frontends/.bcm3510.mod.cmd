cmd_drivers/media/dvb-frontends/bcm3510.mod := printf '%s\n'   bcm3510.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/bcm3510.mod
