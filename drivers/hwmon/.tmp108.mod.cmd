cmd_drivers/hwmon/tmp108.mod := printf '%s\n'   tmp108.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/tmp108.mod
