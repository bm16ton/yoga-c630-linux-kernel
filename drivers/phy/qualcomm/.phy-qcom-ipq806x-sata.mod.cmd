cmd_drivers/phy/qualcomm/phy-qcom-ipq806x-sata.mod := printf '%s\n'   phy-qcom-ipq806x-sata.o | awk '!x[$$0]++ { print("drivers/phy/qualcomm/"$$0) }' > drivers/phy/qualcomm/phy-qcom-ipq806x-sata.mod
