cmd_drivers/hwmon/ltc2947-i2c.mod := printf '%s\n'   ltc2947-i2c.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ltc2947-i2c.mod
