cmd_drivers/media/dvb-frontends/rtl2830.mod := printf '%s\n'   rtl2830.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/rtl2830.mod
