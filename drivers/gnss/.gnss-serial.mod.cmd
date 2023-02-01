cmd_drivers/gnss/gnss-serial.mod := printf '%s\n'   serial.o | awk '!x[$$0]++ { print("drivers/gnss/"$$0) }' > drivers/gnss/gnss-serial.mod
