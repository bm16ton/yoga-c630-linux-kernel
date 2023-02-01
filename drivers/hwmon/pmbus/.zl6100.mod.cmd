cmd_drivers/hwmon/pmbus/zl6100.mod := printf '%s\n'   zl6100.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/zl6100.mod
