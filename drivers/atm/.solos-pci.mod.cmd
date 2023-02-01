cmd_drivers/atm/solos-pci.mod := printf '%s\n'   solos-pci.o | awk '!x[$$0]++ { print("drivers/atm/"$$0) }' > drivers/atm/solos-pci.mod
