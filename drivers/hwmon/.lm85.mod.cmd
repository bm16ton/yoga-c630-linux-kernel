cmd_drivers/hwmon/lm85.mod := printf '%s\n'   lm85.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/lm85.mod
