cmd_drivers/atm/fore_200e.mod := printf '%s\n'   fore200e.o | awk '!x[$$0]++ { print("drivers/atm/"$$0) }' > drivers/atm/fore_200e.mod
