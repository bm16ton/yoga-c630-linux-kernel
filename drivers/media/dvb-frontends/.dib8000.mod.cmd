cmd_drivers/media/dvb-frontends/dib8000.mod := printf '%s\n'   dib8000.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/dib8000.mod
