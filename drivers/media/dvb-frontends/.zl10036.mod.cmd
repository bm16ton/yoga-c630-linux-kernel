cmd_drivers/media/dvb-frontends/zl10036.mod := printf '%s\n'   zl10036.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/zl10036.mod
