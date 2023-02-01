cmd_drivers/base/regmap/regmap-sdw.mod := printf '%s\n'   regmap-sdw.o | awk '!x[$$0]++ { print("drivers/base/regmap/"$$0) }' > drivers/base/regmap/regmap-sdw.mod
