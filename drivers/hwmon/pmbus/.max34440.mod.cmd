cmd_drivers/hwmon/pmbus/max34440.mod := printf '%s\n'   max34440.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/max34440.mod
