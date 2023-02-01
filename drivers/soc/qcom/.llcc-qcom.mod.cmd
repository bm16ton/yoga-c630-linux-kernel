cmd_drivers/soc/qcom/llcc-qcom.mod := printf '%s\n'   llcc-qcom.o | awk '!x[$$0]++ { print("drivers/soc/qcom/"$$0) }' > drivers/soc/qcom/llcc-qcom.mod
