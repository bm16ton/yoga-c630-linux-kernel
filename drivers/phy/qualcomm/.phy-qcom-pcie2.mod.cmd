cmd_drivers/phy/qualcomm/phy-qcom-pcie2.mod := printf '%s\n'   phy-qcom-pcie2.o | awk '!x[$$0]++ { print("drivers/phy/qualcomm/"$$0) }' > drivers/phy/qualcomm/phy-qcom-pcie2.mod
