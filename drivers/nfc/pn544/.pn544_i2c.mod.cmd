cmd_drivers/nfc/pn544/pn544_i2c.mod := printf '%s\n'   i2c.o | awk '!x[$$0]++ { print("drivers/nfc/pn544/"$$0) }' > drivers/nfc/pn544/pn544_i2c.mod
