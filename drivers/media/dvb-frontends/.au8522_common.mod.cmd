cmd_drivers/media/dvb-frontends/au8522_common.mod := printf '%s\n'   au8522_common.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/au8522_common.mod
