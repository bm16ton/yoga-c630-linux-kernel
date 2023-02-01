cmd_drivers/soc/qcom/mdt_loader.mod := printf '%s\n'   mdt_loader.o | awk '!x[$$0]++ { print("drivers/soc/qcom/"$$0) }' > drivers/soc/qcom/mdt_loader.mod
