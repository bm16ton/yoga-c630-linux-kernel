cmd_drivers/nfc/fdp/fdp_i2c.mod := printf '%s\n'   i2c.o | awk '!x[$$0]++ { print("drivers/nfc/fdp/"$$0) }' > drivers/nfc/fdp/fdp_i2c.mod
