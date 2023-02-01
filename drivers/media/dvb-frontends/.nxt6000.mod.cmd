cmd_drivers/media/dvb-frontends/nxt6000.mod := printf '%s\n'   nxt6000.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/nxt6000.mod
