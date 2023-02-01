cmd_drivers/hwmon/ds620.mod := printf '%s\n'   ds620.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ds620.mod
