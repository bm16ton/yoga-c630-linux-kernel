cmd_drivers/media/dvb-frontends/drxk.mod := printf '%s\n'   drxk_hard.o | awk '!x[$$0]++ { print("drivers/media/dvb-frontends/"$$0) }' > drivers/media/dvb-frontends/drxk.mod
