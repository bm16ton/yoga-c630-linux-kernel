cmd_drivers/hwmon/tmp102.mod := printf '%s\n'   tmp102.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/tmp102.mod
