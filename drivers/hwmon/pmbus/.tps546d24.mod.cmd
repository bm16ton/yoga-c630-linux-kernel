cmd_drivers/hwmon/pmbus/tps546d24.mod := printf '%s\n'   tps546d24.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/tps546d24.mod
