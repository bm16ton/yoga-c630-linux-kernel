cmd_drivers/hwmon/lm93.mod := printf '%s\n'   lm93.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/lm93.mod
