cmd_drivers/hwmon/w83l785ts.mod := printf '%s\n'   w83l785ts.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/w83l785ts.mod
