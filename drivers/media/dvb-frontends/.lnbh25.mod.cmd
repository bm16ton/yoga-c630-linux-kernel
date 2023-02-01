cmd_drivers/media/dvb-frontends/lnbh25.mod := printf '%s\n'   lnbh25.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/lnbh25.mod
