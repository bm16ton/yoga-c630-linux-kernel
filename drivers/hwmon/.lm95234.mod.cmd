cmd_drivers/hwmon/lm95234.mod := printf '%s\n'   lm95234.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/lm95234.mod
