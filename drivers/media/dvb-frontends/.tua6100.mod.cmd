cmd_drivers/media/dvb-frontends/tua6100.mod := printf '%s\n'   tua6100.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/tua6100.mod
