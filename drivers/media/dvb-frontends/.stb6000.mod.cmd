cmd_drivers/media/dvb-frontends/stb6000.mod := printf '%s\n'   stb6000.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/stb6000.mod
