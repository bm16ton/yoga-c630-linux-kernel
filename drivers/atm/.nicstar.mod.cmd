cmd_drivers/atm/nicstar.mod := printf '%s\n'   nicstar.o | awk '!x[$$0]++ { print("drivers/atm/"$$0) }' > drivers/atm/nicstar.mod
