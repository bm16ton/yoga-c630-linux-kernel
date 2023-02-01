cmd_drivers/hwmon/pmbus/mp2888.mod := printf '%s\n'   mp2888.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/mp2888.mod
