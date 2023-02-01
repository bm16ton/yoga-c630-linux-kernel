cmd_drivers/hwmon/lm75.mod := printf '%s\n'   lm75.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/lm75.mod
