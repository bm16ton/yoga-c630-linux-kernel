cmd_drivers/hwmon/pmbus/ir38064.mod := printf '%s\n'   ir38064.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/ir38064.mod
