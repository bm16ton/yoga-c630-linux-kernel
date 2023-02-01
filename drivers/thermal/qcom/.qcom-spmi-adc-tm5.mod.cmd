cmd_drivers/thermal/qcom/qcom-spmi-adc-tm5.mod := printf '%s\n'   qcom-spmi-adc-tm5.o | awk '!x[$$0]++ { print("drivers/thermal/qcom/"$$0) }' > drivers/thermal/qcom/qcom-spmi-adc-tm5.mod
