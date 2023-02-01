cmd_drivers/soc/qcom/icc-bwmon.mod := printf '%s\n'   icc-bwmon.o | awk '!x[$$0]++ { print("drivers/soc/qcom/"$$0) }' > drivers/soc/qcom/icc-bwmon.mod
