cmd_drivers/hwmon/pmbus/max16601.mod := printf '%s\n'   max16601.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/max16601.mod
