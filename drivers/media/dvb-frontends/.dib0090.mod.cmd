cmd_drivers/media/dvb-frontends/dib0090.mod := printf '%s\n'   dib0090.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/dib0090.mod
