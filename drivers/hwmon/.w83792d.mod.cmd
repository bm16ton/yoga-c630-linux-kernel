cmd_drivers/hwmon/w83792d.mod := printf '%s\n'   w83792d.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/w83792d.mod
