cmd_drivers/phy/qualcomm/phy-qcom-usb-hsic.mod := printf '%s\n'   phy-qcom-usb-hsic.o | awk '!x[$$0]++ { print("drivers/phy/qualcomm/"$$0) }' > drivers/phy/qualcomm/phy-qcom-usb-hsic.mod
