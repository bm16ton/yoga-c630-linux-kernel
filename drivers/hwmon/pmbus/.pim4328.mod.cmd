cmd_drivers/hwmon/pmbus/pim4328.mod := printf '%s\n'   pim4328.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/pim4328.mod
