cmd_drivers/hwmon/pmbus/pmbus_core.mod := printf '%s\n'   pmbus_core.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/pmbus_core.mod
