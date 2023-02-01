cmd_drivers/hwmon/pmbus/isl68137.mod := printf '%s\n'   isl68137.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/isl68137.mod
