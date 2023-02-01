cmd_drivers/iio/dac/mcp4922.mod := printf '%s\n'   mcp4922.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/mcp4922.mod
