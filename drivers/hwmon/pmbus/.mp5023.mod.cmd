cmd_drivers/hwmon/pmbus/mp5023.mod := printf '%s\n'   mp5023.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/mp5023.mod
