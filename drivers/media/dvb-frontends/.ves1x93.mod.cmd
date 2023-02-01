cmd_drivers/media/dvb-frontends/ves1x93.mod := printf '%s\n'   ves1x93.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/ves1x93.mod
