cmd_drivers/soc/qcom/pdr_interface.mod := printf '%s\n'   pdr_interface.o | awk '!x[$$0]++ { print("drivers/soc/qcom/"$$0) }' > drivers/soc/qcom/pdr_interface.mod
