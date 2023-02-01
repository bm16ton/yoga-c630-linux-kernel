cmd_drivers/iio/adc/nau7802.mod := printf '%s\n'   nau7802.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/nau7802.mod
