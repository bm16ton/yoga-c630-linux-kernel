cmd_drivers/media/dvb-frontends/lgdt330x.mod := printf '%s\n'   lgdt330x.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/lgdt330x.mod
