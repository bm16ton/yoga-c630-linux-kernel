cmd_drivers/hwmon/pmbus/tps40422.mod := printf '%s\n'   tps40422.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/tps40422.mod
