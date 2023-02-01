cmd_drivers/media/dvb-frontends/dvb_dummy_fe.mod := printf '%s\n'   dvb_dummy_fe.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/dvb_dummy_fe.mod
