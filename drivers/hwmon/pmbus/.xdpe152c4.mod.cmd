cmd_drivers/hwmon/pmbus/xdpe152c4.mod := printf '%s\n'   xdpe152c4.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/xdpe152c4.mod
