cmd_drivers/media/dvb-frontends/dib7000m.mod := printf '%s\n'   dib7000m.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/dib7000m.mod
