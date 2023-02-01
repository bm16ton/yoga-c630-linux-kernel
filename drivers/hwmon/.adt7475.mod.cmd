cmd_drivers/hwmon/adt7475.mod := printf '%s\n'   adt7475.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/adt7475.mod
