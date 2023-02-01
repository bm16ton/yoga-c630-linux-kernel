cmd_drivers/hwmon/pmbus/ir36021.mod := printf '%s\n'   ir36021.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/ir36021.mod
