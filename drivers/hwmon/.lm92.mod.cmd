cmd_drivers/hwmon/lm92.mod := printf '%s\n'   lm92.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/lm92.mod
