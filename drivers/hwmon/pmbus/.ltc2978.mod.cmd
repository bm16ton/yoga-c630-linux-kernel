cmd_drivers/hwmon/pmbus/ltc2978.mod := printf '%s\n'   ltc2978.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/ltc2978.mod
