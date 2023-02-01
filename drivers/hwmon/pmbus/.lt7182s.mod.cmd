cmd_drivers/hwmon/pmbus/lt7182s.mod := printf '%s\n'   lt7182s.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/lt7182s.mod
