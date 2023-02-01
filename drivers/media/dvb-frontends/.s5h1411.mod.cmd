cmd_drivers/media/dvb-frontends/s5h1411.mod := printf '%s\n'   s5h1411.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/s5h1411.mod
