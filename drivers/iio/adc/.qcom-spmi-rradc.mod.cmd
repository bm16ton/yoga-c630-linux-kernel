cmd_drivers/iio/adc/qcom-spmi-rradc.mod := printf '%s\n'   qcom-spmi-rradc.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/qcom-spmi-rradc.mod
