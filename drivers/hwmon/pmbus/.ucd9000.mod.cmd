cmd_drivers/hwmon/pmbus/ucd9000.mod := printf '%s\n'   ucd9000.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/ucd9000.mod
