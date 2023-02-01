cmd_drivers/iio/adc/sd_adc_modulator.mod := printf '%s\n'   sd_adc_modulator.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/sd_adc_modulator.mod
