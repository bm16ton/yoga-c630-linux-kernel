cmd_drivers/nfc/st-nci/st-nci_i2c.mod := printf '%s\n'   i2c.o | awk '!x[$$0]++ { print("drivers/nfc/st-nci/"$$0) }' > drivers/nfc/st-nci/st-nci_i2c.mod
