cmd_drivers/hwmon/pmbus/ir35221.mod := printf '%s\n'   ir35221.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/ir35221.mod
