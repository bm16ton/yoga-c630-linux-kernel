cmd_drivers/media/dvb-frontends/dib0070.mod := printf '%s\n'   dib0070.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/dib0070.mod
