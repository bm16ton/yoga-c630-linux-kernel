cmd_drivers/mfd/tps65217.mod := printf '%s\n'   tps65217.o | awk '!x[$$0]++ { print("drivers/mfd/"$$0) }' > drivers/mfd/tps65217.mod
