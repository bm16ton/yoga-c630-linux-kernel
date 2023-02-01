cmd_drivers/hwmon/sht3x.mod := printf '%s\n'   sht3x.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/sht3x.mod
