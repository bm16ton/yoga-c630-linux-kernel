cmd_drivers/hwmon/pmbus/max16064.mod := printf '%s\n'   max16064.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/max16064.mod
