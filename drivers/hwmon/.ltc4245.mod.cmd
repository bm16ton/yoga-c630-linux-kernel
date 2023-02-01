cmd_drivers/hwmon/ltc4245.mod := printf '%s\n'   ltc4245.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ltc4245.mod
