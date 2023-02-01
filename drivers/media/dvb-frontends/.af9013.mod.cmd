cmd_drivers/media/dvb-frontends/af9013.mod := printf '%s\n'   af9013.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/af9013.mod
