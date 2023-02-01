cmd_drivers/hwmon/ltc2947-core.mod := printf '%s\n'   ltc2947-core.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ltc2947-core.mod
