cmd_drivers/hwmon/ltc4261.mod := printf '%s\n'   ltc4261.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ltc4261.mod
