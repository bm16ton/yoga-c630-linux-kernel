cmd_drivers/iio/adc/envelope-detector.mod := printf '%s\n'   envelope-detector.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/envelope-detector.mod
