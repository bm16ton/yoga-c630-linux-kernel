cmd_drivers/hwmon/adt7411.mod := printf '%s\n'   adt7411.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/adt7411.mod
