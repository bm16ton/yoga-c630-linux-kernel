cmd_drivers/hwmon/drivetemp.mod := printf '%s\n'   drivetemp.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/drivetemp.mod
