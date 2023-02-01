cmd_drivers/hwmon/ad7414.mod := printf '%s\n'   ad7414.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ad7414.mod
