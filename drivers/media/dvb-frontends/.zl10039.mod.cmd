cmd_drivers/media/dvb-frontends/zl10039.mod := printf '%s\n'   zl10039.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/zl10039.mod
