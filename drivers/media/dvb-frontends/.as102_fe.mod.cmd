cmd_drivers/media/dvb-frontends/as102_fe.mod := printf '%s\n'   as102_fe.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/as102_fe.mod
