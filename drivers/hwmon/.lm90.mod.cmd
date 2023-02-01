cmd_drivers/hwmon/lm90.mod := printf '%s\n'   lm90.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/lm90.mod
