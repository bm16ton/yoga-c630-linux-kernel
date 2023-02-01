cmd_drivers/hwmon/sht21.mod := printf '%s\n'   sht21.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/sht21.mod
