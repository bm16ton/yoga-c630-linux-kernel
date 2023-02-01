cmd_drivers/mfd/viperboard.mod := printf '%s\n'   viperboard.o | awk '!x[$$0]++ { print("drivers/mfd/"$$0) }' > drivers/mfd/viperboard.mod
