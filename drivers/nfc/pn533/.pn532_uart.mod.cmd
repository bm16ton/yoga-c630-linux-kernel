cmd_drivers/nfc/pn533/pn532_uart.mod := printf '%s\n'   uart.o | awk '!x[$$0]++ { print("drivers/nfc/pn533/"$$0) }' > drivers/nfc/pn533/pn532_uart.mod
