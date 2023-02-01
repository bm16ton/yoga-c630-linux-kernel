cmd_drivers/nfc/st21nfca/st21nfca_i2c.mod := printf '%s\n'   i2c.o | awk '!x[$$0]++ { print("drivers/nfc/st21nfca/"$$0) }' > drivers/nfc/st21nfca/st21nfca_i2c.mod
