cmd_drivers/media/dvb-frontends/gp8psk-fe.mod := printf '%s\n'   gp8psk-fe.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/gp8psk-fe.mod
