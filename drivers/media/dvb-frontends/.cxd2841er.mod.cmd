cmd_drivers/media/dvb-frontends/cxd2841er.mod := printf '%s\n'   cxd2841er.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/cxd2841er.mod
