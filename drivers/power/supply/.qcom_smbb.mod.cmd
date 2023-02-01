cmd_drivers/power/supply/qcom_smbb.mod := printf '%s\n'   qcom_smbb.o | awk '!x[$$0]++ { print("drivers/power/supply/"$$0) }' > drivers/power/supply/qcom_smbb.mod
