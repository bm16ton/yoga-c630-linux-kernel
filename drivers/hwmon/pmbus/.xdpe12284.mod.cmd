cmd_drivers/hwmon/pmbus/xdpe12284.mod := printf '%s\n'   xdpe12284.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/xdpe12284.mod
