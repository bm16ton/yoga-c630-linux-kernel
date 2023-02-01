cmd_drivers/hwmon/tmp103.mod := printf '%s\n'   tmp103.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/tmp103.mod
