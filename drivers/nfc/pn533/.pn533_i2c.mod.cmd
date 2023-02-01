cmd_drivers/nfc/pn533/pn533_i2c.mod := printf '%s\n'   i2c.o | awk '!x[$$0]++ { print("drivers/nfc/pn533/"$$0) }' > drivers/nfc/pn533/pn533_i2c.mod
