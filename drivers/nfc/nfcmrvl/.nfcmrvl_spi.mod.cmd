cmd_drivers/nfc/nfcmrvl/nfcmrvl_spi.mod := printf '%s\n'   spi.o | awk '!x[$$0]++ { print("drivers/nfc/nfcmrvl/"$$0) }' > drivers/nfc/nfcmrvl/nfcmrvl_spi.mod
