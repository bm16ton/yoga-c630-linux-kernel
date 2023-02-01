cmd_drivers/media/dvb-frontends/atbm8830.mod := printf '%s\n'   atbm8830.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/atbm8830.mod
