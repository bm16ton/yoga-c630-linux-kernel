cmd_drivers/media/dvb-frontends/stb0899.mod := printf '%s\n'   stb0899_drv.o stb0899_algo.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/stb0899.mod
