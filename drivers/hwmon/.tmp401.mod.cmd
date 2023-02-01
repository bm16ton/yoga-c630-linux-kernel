cmd_drivers/hwmon/tmp401.mod := printf '%s\n'   tmp401.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/tmp401.mod
