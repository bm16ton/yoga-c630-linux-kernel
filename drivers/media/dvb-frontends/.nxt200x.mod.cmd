cmd_drivers/media/dvb-frontends/nxt200x.mod := printf '%s\n'   nxt200x.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/nxt200x.mod
