cmd_drivers/hwmon/ad7418.mod := printf '%s\n'   ad7418.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ad7418.mod
