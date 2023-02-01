cmd_drivers/media/dvb-frontends/mt312.mod := printf '%s\n'   mt312.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/mt312.mod
