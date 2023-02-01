cmd_drivers/media/dvb-frontends/lgdt3306a.mod := printf '%s\n'   lgdt3306a.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/lgdt3306a.mod
