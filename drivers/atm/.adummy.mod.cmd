cmd_drivers/atm/adummy.mod := printf '%s\n'   adummy.o | awk '!x[$$0]++ { print("drivers/atm/"$$0) }' > drivers/atm/adummy.mod
