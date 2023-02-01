cmd_drivers/media/dvb-frontends/dib3000mb.mod := printf '%s\n'   dib3000mb.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/dib3000mb.mod
