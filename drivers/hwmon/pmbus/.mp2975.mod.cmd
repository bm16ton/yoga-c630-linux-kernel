cmd_drivers/hwmon/pmbus/mp2975.mod := printf '%s\n'   mp2975.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/mp2975.mod
