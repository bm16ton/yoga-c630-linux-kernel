cmd_drivers/hwmon/amc6821.mod := printf '%s\n'   amc6821.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/amc6821.mod
