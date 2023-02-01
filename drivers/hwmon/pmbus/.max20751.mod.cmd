cmd_drivers/hwmon/pmbus/max20751.mod := printf '%s\n'   max20751.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/max20751.mod
