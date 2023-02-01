cmd_drivers/hwmon/w83627ehf.mod := printf '%s\n'   w83627ehf.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/w83627ehf.mod
