cmd_drivers/tty/serial/rp2.mod := printf '%s\n'   rp2.o | awk '!x[$$0]++ { print("drivers/tty/serial/"$$0) }' > drivers/tty/serial/rp2.mod
