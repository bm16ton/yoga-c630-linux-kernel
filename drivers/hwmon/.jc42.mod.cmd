cmd_drivers/hwmon/jc42.mod := printf '%s\n'   jc42.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/jc42.mod
