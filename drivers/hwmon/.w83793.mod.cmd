cmd_drivers/hwmon/w83793.mod := printf '%s\n'   w83793.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/w83793.mod
