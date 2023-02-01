cmd_drivers/media/rc/rc-loopback.mod := printf '%s\n'   rc-loopback.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/rc-loopback.mod
