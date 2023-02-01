cmd_drivers/iio/adc/ad_sigma_delta.mod := printf '%s\n'   ad_sigma_delta.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/ad_sigma_delta.mod
