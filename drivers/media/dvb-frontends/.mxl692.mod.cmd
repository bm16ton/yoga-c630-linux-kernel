cmd_drivers/media/dvb-frontends/mxl692.mod := printf '%s\n'   mxl692.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/mxl692.mod
