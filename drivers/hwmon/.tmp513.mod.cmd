cmd_drivers/hwmon/tmp513.mod := printf '%s\n'   tmp513.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/tmp513.mod
