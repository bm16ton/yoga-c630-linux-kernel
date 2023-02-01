cmd_drivers/hwmon/pc87360.mod := printf '%s\n'   pc87360.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/pc87360.mod
