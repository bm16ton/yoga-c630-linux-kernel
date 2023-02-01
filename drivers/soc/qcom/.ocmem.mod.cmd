cmd_drivers/soc/qcom/ocmem.mod := printf '%s\n'   ocmem.o | awk '!x[$$0]++ { print("drivers/soc/qcom/"$$0) }' > drivers/soc/qcom/ocmem.mod
