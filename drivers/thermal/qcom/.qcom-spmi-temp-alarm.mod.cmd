cmd_drivers/thermal/qcom/qcom-spmi-temp-alarm.mod := printf '%s\n'   qcom-spmi-temp-alarm.o | awk '!x[$$0]++ { print("drivers/thermal/qcom/"$$0) }' > drivers/thermal/qcom/qcom-spmi-temp-alarm.mod
