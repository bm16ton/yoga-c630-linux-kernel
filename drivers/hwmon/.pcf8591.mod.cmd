cmd_drivers/hwmon/pcf8591.mod := printf '%s\n'   pcf8591.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/pcf8591.mod
