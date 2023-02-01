cmd_drivers/hwmon/adt7310.mod := printf '%s\n'   adt7310.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/adt7310.mod
