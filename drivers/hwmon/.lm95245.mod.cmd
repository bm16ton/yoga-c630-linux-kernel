cmd_drivers/hwmon/lm95245.mod := printf '%s\n'   lm95245.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/lm95245.mod
