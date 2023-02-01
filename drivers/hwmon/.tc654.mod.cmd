cmd_drivers/hwmon/tc654.mod := printf '%s\n'   tc654.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/tc654.mod
