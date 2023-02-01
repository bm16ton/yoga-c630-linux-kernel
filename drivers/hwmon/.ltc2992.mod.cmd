cmd_drivers/hwmon/ltc2992.mod := printf '%s\n'   ltc2992.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ltc2992.mod
