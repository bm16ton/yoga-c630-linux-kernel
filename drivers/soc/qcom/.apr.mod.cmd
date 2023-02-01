cmd_drivers/soc/qcom/apr.mod := printf '%s\n'   apr.o | awk '!x[$$0]++ { print("drivers/soc/qcom/"$$0) }' > drivers/soc/qcom/apr.mod
