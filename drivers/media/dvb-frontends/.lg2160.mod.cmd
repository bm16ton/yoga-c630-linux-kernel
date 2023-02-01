cmd_drivers/media/dvb-frontends/lg2160.mod := printf '%s\n'   lg2160.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/lg2160.mod
