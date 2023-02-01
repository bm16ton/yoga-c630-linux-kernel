cmd_drivers/hwmon/ltc4151.mod := printf '%s\n'   ltc4151.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ltc4151.mod
