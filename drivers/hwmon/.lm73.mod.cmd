cmd_drivers/hwmon/lm73.mod := printf '%s\n'   lm73.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/lm73.mod
