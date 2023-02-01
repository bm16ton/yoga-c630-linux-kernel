cmd_drivers/mfd/wcd934x.mod := printf '%s\n'   wcd934x.o | awk '!x[$$0]++ { print("drivers/mfd/"$$0) }' > drivers/mfd/wcd934x.mod
