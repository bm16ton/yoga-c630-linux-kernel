cmd_drivers/hwmon/ltc4215.mod := printf '%s\n'   ltc4215.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ltc4215.mod
