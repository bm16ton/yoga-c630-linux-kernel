cmd_drivers/nfc/nfcmrvl/nfcmrvl_uart.mod := printf '%s\n'   uart.o | awk '!x[$$0]++ { print("drivers/nfc/nfcmrvl/"$$0) }' > drivers/nfc/nfcmrvl/nfcmrvl_uart.mod
