cmd_drivers/hwmon/max31722.mod := printf '%s\n'   max31722.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/max31722.mod
