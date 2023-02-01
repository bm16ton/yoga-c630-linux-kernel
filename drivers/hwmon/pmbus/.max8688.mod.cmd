cmd_drivers/hwmon/pmbus/max8688.mod := printf '%s\n'   max8688.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/max8688.mod
