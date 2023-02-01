cmd_drivers/soc/qcom/wcnss_ctrl.mod := printf '%s\n'   wcnss_ctrl.o | awk '!x[$$0]++ { print("drivers/soc/qcom/"$$0) }' > drivers/soc/qcom/wcnss_ctrl.mod
