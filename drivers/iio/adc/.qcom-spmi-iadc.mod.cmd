cmd_drivers/iio/adc/qcom-spmi-iadc.mod := printf '%s\n'   qcom-spmi-iadc.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/qcom-spmi-iadc.mod
