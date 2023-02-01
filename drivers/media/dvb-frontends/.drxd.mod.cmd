cmd_drivers/media/dvb-frontends/drxd.mod := printf '%s\n'   drxd_firm.o drxd_hard.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/drxd.mod
