cmd_drivers/media/dvb-frontends/cx24120.mod := printf '%s\n'   cx24120.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/cx24120.mod
