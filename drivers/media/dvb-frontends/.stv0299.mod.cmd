cmd_drivers/media/dvb-frontends/stv0299.mod := printf '%s\n'   stv0299.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/stv0299.mod
