cmd_drivers/hwmon/ltc2990.mod := printf '%s\n'   ltc2990.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ltc2990.mod
