cmd_drivers/hwmon/pmbus/irps5401.mod := printf '%s\n'   irps5401.o | awk '!x[$$0]++ { print("drivers/hwmon/pmbus/"$$0) }' > drivers/hwmon/pmbus/irps5401.mod
