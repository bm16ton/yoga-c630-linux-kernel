cmd_drivers/media/dvb-frontends/cx24116.mod := printf '%s\n'   cx24116.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/cx24116.mod
