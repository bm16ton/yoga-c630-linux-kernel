cmd_drivers/hwmon/ad7314.mod := printf '%s\n'   ad7314.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ad7314.mod
