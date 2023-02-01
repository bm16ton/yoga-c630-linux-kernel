cmd_drivers/soc/qcom/pmic_glink.mod := printf '%s\n'   pmic_glink.o | awk '!x[$$0]++ { print("drivers/soc/qcom/"$$0) }' > drivers/soc/qcom/pmic_glink.mod
