cmd_drivers/hwmon/hih6130.mod := printf '%s\n'   hih6130.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/hih6130.mod
