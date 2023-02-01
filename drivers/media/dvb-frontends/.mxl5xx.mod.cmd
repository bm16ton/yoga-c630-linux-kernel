cmd_drivers/media/dvb-frontends/mxl5xx.mod := printf '%s\n'   mxl5xx.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/mxl5xx.mod
