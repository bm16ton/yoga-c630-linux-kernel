cmd_drivers/hwmon/max31790.mod := printf '%s\n'   max31790.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/max31790.mod
