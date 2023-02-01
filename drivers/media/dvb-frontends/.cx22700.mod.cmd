cmd_drivers/media/dvb-frontends/cx22700.mod := printf '%s\n'   cx22700.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/cx22700.mod
