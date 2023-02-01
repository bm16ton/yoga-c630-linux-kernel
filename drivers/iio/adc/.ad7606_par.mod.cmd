cmd_drivers/iio/adc/ad7606_par.mod := printf '%s\n'   ad7606_par.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad7606_par.mod
