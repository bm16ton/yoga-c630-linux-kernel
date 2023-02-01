cmd_drivers/media/dvb-frontends/lgs8gxx.mod := printf '%s\n'   lgs8gxx.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/lgs8gxx.mod
