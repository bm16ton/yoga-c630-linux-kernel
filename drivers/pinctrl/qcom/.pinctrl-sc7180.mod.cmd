cmd_drivers/pinctrl/qcom/pinctrl-sc7180.mod := printf '%s\n'   pinctrl-sc7180.o | awk '!x[$$0]++ { print("drivers/pinctrl/qcom/"$$0) }' > drivers/pinctrl/qcom/pinctrl-sc7180.mod
