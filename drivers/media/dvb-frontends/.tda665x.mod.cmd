cmd_drivers/media/dvb-frontends/tda665x.mod := printf '%s\n'   tda665x.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/tda665x.mod
