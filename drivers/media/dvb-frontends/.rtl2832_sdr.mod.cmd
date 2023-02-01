cmd_drivers/media/dvb-frontends/rtl2832_sdr.mod := printf '%s\n'   rtl2832_sdr.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/rtl2832_sdr.mod
