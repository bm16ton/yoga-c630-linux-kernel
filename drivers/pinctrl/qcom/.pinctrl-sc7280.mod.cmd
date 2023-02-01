cmd_drivers/pinctrl/qcom/pinctrl-sc7280.mod := printf '%s\n'   pinctrl-sc7280.o | awk '!x[$$0]++ { print("drivers/pinctrl/qcom/"$$0) }' > drivers/pinctrl/qcom/pinctrl-sc7280.mod
