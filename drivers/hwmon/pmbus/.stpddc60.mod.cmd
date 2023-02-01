cmd_drivers/hwmon/pmbus/stpddc60.mod := printf '%s\n'   stpddc60.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/stpddc60.mod
