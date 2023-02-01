cmd_drivers/hwmon/lm95241.mod := printf '%s\n'   lm95241.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/lm95241.mod
