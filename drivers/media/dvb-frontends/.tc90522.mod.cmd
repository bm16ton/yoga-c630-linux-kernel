cmd_drivers/media/dvb-frontends/tc90522.mod := printf '%s\n'   tc90522.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/tc90522.mod
