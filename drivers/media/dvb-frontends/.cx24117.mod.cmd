cmd_drivers/media/dvb-frontends/cx24117.mod := printf '%s\n'   cx24117.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/cx24117.mod
