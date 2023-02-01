cmd_drivers/iio/adc/mcp320x.mod := printf '%s\n'   mcp320x.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/mcp320x.mod
