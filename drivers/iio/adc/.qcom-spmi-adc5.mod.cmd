cmd_drivers/iio/adc/qcom-spmi-adc5.mod := printf '%s\n'   qcom-spmi-adc5.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/qcom-spmi-adc5.mod
