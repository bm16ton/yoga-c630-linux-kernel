cmd_drivers/hwmon/shtc1.mod := printf '%s\n'   shtc1.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/shtc1.mod
