cmd_drivers/iio/adc/qcom-spmi-vadc.mod := printf '%s\n'   qcom-spmi-vadc.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/qcom-spmi-vadc.mod
