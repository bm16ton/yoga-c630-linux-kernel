cmd_drivers/media/dvb-frontends/l64781.mod := printf '%s\n'   l64781.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/l64781.mod
