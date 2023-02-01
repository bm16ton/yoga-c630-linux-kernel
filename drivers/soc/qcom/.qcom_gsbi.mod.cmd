cmd_drivers/soc/qcom/qcom_gsbi.mod := printf '%s\n'   qcom_gsbi.o | awk '!x[$$0]++ { print("drivers/soc/qcom/"$$0) }' > drivers/soc/qcom/qcom_gsbi.mod
