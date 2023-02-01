cmd_drivers/atm/iphase.mod := printf '%s\n'   iphase.o | awk '!x[$$0]++ { print("drivers/atm/"$$0) }' > drivers/atm/iphase.mod
