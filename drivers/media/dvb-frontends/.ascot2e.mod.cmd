cmd_drivers/media/dvb-frontends/ascot2e.mod := printf '%s\n'   ascot2e.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/ascot2e.mod
