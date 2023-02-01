cmd_drivers/media/dvb-frontends/mb86a16.mod := printf '%s\n'   mb86a16.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/mb86a16.mod
