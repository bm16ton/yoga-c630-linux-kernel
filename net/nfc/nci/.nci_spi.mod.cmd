cmd_net/nfc/nci/nci_spi.mod := printf '%s\n'   spi.o | awk '!x[$$0]++ { print("net/nfc/nci/"$$0) }' > net/nfc/nci/nci_spi.mod
