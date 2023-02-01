cmd_drivers/mfd/dln2.mod := printf '%s\n'   dln2.o | awk '!x[$$0]++ { print("drivers/mfd/"$$0) }' > drivers/mfd/dln2.mod
