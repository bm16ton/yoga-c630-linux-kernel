cmd_drivers/iio/adc/mcp3911.mod := printf '%s\n'   mcp3911.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/mcp3911.mod
