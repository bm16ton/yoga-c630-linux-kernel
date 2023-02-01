cmd_drivers/base/regmap/regmap-slimbus.mod := printf '%s\n'   regmap-slimbus.o | awk '!x[$$0]++ { print("drivers/base/regmap/"$$0) }' > drivers/base/regmap/regmap-slimbus.mod
