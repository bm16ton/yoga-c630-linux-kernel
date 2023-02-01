cmd_drivers/nfc/nfcmrvl/nfcmrvl_i2c.mod := printf '%s\n'   i2c.o | awk '!x[$$0]++ { print("drivers/nfc/nfcmrvl/"$$0) }' > drivers/nfc/nfcmrvl/nfcmrvl_i2c.mod
