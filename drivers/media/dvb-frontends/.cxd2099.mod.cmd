cmd_drivers/media/dvb-frontends/cxd2099.mod := printf '%s\n'   cxd2099.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/cxd2099.mod
