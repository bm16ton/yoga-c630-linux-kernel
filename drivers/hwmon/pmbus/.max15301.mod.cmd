cmd_drivers/hwmon/pmbus/max15301.mod := printf '%s\n'   max15301.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/max15301.mod
