cmd_drivers/hwmon/pmbus/max20730.mod := printf '%s\n'   max20730.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/max20730.mod
