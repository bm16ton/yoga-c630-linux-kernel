cmd_drivers/atm/suni.mod := printf '%s\n'   suni.o | awk '!x[$$0]++ { print("drivers/atm/"$$0) }' > drivers/atm/suni.mod
