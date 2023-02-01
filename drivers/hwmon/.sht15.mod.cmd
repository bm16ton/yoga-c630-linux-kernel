cmd_drivers/hwmon/sht15.mod := printf '%s\n'   sht15.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/sht15.mod
