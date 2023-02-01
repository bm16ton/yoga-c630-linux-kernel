cmd_drivers/soundwire/soundwire-qcom.mod := printf '%s\n'   qcom.o | awk '!x[$$0]++ { print("drivers/soundwire/"$$0) }' > drivers/soundwire/soundwire-qcom.mod
