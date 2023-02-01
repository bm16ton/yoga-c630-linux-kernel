cmd_drivers/iio/adc/mcp3422.mod := printf '%s\n'   mcp3422.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/mcp3422.mod
