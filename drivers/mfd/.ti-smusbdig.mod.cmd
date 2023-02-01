cmd_drivers/mfd/ti-smusbdig.mod := printf '%s\n'   ti-smusbdig.o | awk '!x[$$0]++ { print("drivers/mfd/"$$0) }' > drivers/mfd/ti-smusbdig.mod
