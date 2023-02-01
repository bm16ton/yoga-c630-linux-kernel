cmd_drivers/media/dvb-frontends/lnbp22.mod := printf '%s\n'   lnbp22.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/lnbp22.mod
