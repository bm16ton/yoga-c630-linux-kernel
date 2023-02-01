cmd_drivers/power/supply/qcom_pmic_glink_power.mod := printf '%s\n'   qcom_pmic_glink_power.o | awk '!x[$$0]++ { print("drivers/power/supply/"$$0) }' > drivers/power/supply/qcom_pmic_glink_power.mod
