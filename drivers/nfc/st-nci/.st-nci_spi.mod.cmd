cmd_drivers/nfc/st-nci/st-nci_spi.mod := printf '%s\n'   spi.o | awk '!x[$$0]++ { print("drivers/nfc/st-nci/"$$0) }' > drivers/nfc/st-nci/st-nci_spi.mod
