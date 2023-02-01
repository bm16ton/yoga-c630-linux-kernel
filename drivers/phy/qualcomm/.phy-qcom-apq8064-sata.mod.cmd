cmd_drivers/phy/qualcomm/phy-qcom-apq8064-sata.mod := printf '%s\n'   phy-qcom-apq8064-sata.o | awk '!x[$$0]++ { print("drivers/phy/qualcomm/"$$0) }' > drivers/phy/qualcomm/phy-qcom-apq8064-sata.mod
