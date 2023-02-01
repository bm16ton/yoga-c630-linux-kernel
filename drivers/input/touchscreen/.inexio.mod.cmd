cmd_drivers/input/touchscreen/inexio.mod := printf '%s\n'   inexio.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/inexio.mod
