cmd_drivers/hwmon/adt7470.mod := printf '%s\n'   adt7470.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/adt7470.mod
