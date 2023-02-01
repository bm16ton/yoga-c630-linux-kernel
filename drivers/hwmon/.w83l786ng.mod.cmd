cmd_drivers/hwmon/w83l786ng.mod := printf '%s\n'   w83l786ng.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/w83l786ng.mod
