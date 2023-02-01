cmd_drivers/media/dvb-frontends/m88rs2000.mod := printf '%s\n'   m88rs2000.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/m88rs2000.mod
