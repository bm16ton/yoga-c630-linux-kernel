cmd_drivers/hwmon/w83795.mod := printf '%s\n'   w83795.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/w83795.mod
