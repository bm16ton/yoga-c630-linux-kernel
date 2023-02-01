cmd_drivers/hwmon/adt7x10.mod := printf '%s\n'   adt7x10.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/adt7x10.mod
