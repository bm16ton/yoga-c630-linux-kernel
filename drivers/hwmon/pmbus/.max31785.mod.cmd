cmd_drivers/hwmon/pmbus/max31785.mod := printf '%s\n'   max31785.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/max31785.mod
