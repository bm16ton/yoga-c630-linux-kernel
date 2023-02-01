cmd_drivers/media/dvb-frontends/horus3a.mod := printf '%s\n'   horus3a.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/horus3a.mod
