cmd_drivers/hwmon/adt7410.mod := printf '%s\n'   adt7410.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/adt7410.mod
