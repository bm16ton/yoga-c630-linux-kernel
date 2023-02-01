cmd_drivers/hwmon/lm78.mod := printf '%s\n'   lm78.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/lm78.mod
