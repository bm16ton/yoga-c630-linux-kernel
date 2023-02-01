cmd_drivers/hwmon/lm80.mod := printf '%s\n'   lm80.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/lm80.mod
