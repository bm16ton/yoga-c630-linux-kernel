cmd_drivers/hwmon/pmbus/pxe1610.mod := printf '%s\n'   pxe1610.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/pxe1610.mod
