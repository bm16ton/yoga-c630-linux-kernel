cmd_drivers/iio/adc/qcom-vadc-common.mod := printf '%s\n'   qcom-vadc-common.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/qcom-vadc-common.mod
