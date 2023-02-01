cmd_drivers/input/tablet/wacom_serial4.mod := printf '%s\n'   wacom_serial4.o | awk '!x[$$0]++ { print("drivers/input/tablet/"$$0) }' > drivers/input/tablet/wacom_serial4.mod
