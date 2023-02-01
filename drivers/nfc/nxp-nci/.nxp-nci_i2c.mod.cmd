cmd_drivers/nfc/nxp-nci/nxp-nci_i2c.mod := printf '%s\n'   i2c.o | awk '!x[$$0]++ { print("drivers/nfc/nxp-nci/"$$0) }' > drivers/nfc/nxp-nci/nxp-nci_i2c.mod
