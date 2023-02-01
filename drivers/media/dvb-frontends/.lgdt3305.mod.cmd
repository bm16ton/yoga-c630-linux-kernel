cmd_drivers/media/dvb-frontends/lgdt3305.mod := printf '%s\n'   lgdt3305.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/lgdt3305.mod
