cmd_drivers/hwmon/i5k_amb.mod := printf '%s\n'   i5k_amb.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/i5k_amb.mod
