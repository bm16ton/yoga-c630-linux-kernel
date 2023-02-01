cmd_drivers/media/dvb-frontends/lnbp21.mod := printf '%s\n'   lnbp21.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/lnbp21.mod
