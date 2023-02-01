cmd_drivers/base/regmap/regmap-spi.mod := printf '%s\n'   regmap-spi.o | awk '!x[$$0]++ { print("drivers/base/regmap/"$$0) }' > drivers/base/regmap/regmap-spi.mod
