cmd_drivers/media/dvb-frontends/dvb-pll.mod := printf '%s\n'   dvb-pll.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/dvb-pll.mod
