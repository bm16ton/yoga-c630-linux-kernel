cmd_drivers/nfc/s3fwrn5/s3fwrn82_uart.mod := printf '%s\n'   uart.o | awk '!x[$$0]++ { print("drivers/nfc/s3fwrn5/"$$0) }' > drivers/nfc/s3fwrn5/s3fwrn82_uart.mod
