cmd_drivers/hwmon/pmbus/pmbus.mod := printf '%s\n'   pmbus.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/pmbus.mod
