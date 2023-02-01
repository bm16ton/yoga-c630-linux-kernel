cmd_drivers/hwmon/sht4x.mod := printf '%s\n'   sht4x.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/sht4x.mod
