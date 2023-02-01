cmd_drivers/hwmon/lm87.mod := printf '%s\n'   lm87.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/lm87.mod
