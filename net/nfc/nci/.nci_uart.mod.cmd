cmd_net/nfc/nci/nci_uart.mod := printf '%s\n'   uart.o | awk '!x[$$0]++ { print("net/nfc/nci/"$$0) }' > net/nfc/nci/nci_uart.mod
