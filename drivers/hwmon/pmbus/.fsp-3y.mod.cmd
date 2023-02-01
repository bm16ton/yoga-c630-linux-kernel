cmd_drivers/hwmon/pmbus/fsp-3y.mod := printf '%s\n'   fsp-3y.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/fsp-3y.mod
