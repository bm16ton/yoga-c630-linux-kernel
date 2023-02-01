cmd_drivers/hwmon/adt7462.mod := printf '%s\n'   adt7462.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/adt7462.mod
