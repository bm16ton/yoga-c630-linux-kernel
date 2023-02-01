cmd_drivers/iio/dac/mcp4725.mod := printf '%s\n'   mcp4725.o | awk '!x[$$0]++ { print("drivers/iio/dac/"$$0) }' > drivers/iio/dac/mcp4725.mod
