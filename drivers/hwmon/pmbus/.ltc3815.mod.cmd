cmd_drivers/hwmon/pmbus/ltc3815.mod := printf '%s\n'   ltc3815.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/ltc3815.mod
