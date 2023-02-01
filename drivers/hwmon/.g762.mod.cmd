cmd_drivers/hwmon/g762.mod := printf '%s\n'   g762.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/g762.mod
