cmd_drivers/media/pci/smipcie/smipcie.mod := printf '%s\n'   smipcie-main.o smipcie-ir.o | awk '!x[$$0]++ { print("drivers/media/pci/smipcie/"$$0) }' > drivers/media/pci/smipcie/smipcie.mod
