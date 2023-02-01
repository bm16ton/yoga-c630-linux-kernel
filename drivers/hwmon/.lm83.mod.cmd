cmd_drivers/hwmon/lm83.mod := printf '%s\n'   lm83.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/lm83.mod
