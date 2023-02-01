cmd_drivers/media/dvb-frontends/helene.mod := printf '%s\n'   helene.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/helene.mod
