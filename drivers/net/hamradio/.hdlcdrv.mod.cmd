cmd_drivers/net/hamradio/hdlcdrv.mod := printf '%s\n'   hdlcdrv.o | awk '!x[$$0]++ { print("drivers/net/hamradio/"$$0) }' > drivers/net/hamradio/hdlcdrv.mod
