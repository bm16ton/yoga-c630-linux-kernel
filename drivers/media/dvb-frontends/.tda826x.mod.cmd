cmd_drivers/media/dvb-frontends/tda826x.mod := printf '%s\n'   tda826x.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/tda826x.mod
