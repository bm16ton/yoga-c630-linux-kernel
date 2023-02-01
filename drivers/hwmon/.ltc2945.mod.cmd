cmd_drivers/hwmon/ltc2945.mod := printf '%s\n'   ltc2945.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ltc2945.mod
