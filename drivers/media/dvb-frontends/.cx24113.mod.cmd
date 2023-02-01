cmd_drivers/media/dvb-frontends/cx24113.mod := printf '%s\n'   cx24113.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/cx24113.mod
