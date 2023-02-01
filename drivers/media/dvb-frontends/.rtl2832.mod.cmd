cmd_drivers/media/dvb-frontends/rtl2832.mod := printf '%s\n'   rtl2832.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/rtl2832.mod
