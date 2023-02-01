cmd_drivers/phy/qualcomm/phy-qcom-usb-hs.mod := printf '%s\n'   phy-qcom-usb-hs.o | awk '!x[$$0]++ { print("drivers/phy/qualcomm/"$$0) }' > drivers/phy/qualcomm/phy-qcom-usb-hs.mod
