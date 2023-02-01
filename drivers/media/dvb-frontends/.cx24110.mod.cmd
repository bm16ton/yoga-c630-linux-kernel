cmd_drivers/media/dvb-frontends/cx24110.mod := printf '%s\n'   cx24110.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/cx24110.mod
