cmd_drivers/hwmon/w83627hf.mod := printf '%s\n'   w83627hf.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/w83627hf.mod
