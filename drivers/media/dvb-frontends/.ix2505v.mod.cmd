cmd_drivers/media/dvb-frontends/ix2505v.mod := printf '%s\n'   ix2505v.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/ix2505v.mod
