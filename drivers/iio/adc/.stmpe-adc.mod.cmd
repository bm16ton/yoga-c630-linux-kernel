cmd_drivers/iio/adc/stmpe-adc.mod := printf '%s\n'   stmpe-adc.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/stmpe-adc.mod
