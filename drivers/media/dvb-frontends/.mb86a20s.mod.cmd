cmd_drivers/media/dvb-frontends/mb86a20s.mod := printf '%s\n'   mb86a20s.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/mb86a20s.mod
