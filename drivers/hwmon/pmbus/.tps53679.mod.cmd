cmd_drivers/hwmon/pmbus/tps53679.mod := printf '%s\n'   tps53679.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/tps53679.mod
