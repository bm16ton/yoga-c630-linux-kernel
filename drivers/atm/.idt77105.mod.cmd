cmd_drivers/atm/idt77105.mod := printf '%s\n'   idt77105.o | awk '!x[$$0]++ { print("drivers/atm/"$$0) }' > drivers/atm/idt77105.mod
