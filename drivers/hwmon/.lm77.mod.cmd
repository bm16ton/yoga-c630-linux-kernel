cmd_drivers/hwmon/lm77.mod := printf '%s\n'   lm77.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/lm77.mod
