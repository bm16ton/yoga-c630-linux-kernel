cmd_drivers/input/touchscreen/ads7846.mod := printf '%s\n'   ads7846.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/ads7846.mod
