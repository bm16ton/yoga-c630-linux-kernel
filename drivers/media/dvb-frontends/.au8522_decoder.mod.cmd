cmd_drivers/media/dvb-frontends/au8522_decoder.mod := printf '%s\n'   au8522_decoder.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/au8522_decoder.mod
