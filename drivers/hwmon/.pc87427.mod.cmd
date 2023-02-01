cmd_drivers/hwmon/pc87427.mod := printf '%s\n'   pc87427.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/pc87427.mod
