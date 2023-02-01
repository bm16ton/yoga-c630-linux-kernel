cmd_drivers/media/dvb-frontends/dibx000_common.mod := printf '%s\n'   dibx000_common.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/dibx000_common.mod
