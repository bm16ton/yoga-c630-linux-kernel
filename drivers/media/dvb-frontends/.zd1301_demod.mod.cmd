cmd_drivers/media/dvb-frontends/zd1301_demod.mod := printf '%s\n'   zd1301_demod.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/zd1301_demod.mod
