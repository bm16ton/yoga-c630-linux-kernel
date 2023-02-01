cmd_drivers/hwmon/ltc2947-spi.mod := printf '%s\n'   ltc2947-spi.o | awk '!x[$$0]++ { print("drivers/hwmon/"$$0) }' > drivers/hwmon/ltc2947-spi.mod
