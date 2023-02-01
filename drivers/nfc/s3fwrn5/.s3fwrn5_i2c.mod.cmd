cmd_drivers/nfc/s3fwrn5/s3fwrn5_i2c.mod := printf '%s\n'   i2c.o | awk '!x[$$0]++ { print("drivers/nfc/s3fwrn5/"$$0) }' > drivers/nfc/s3fwrn5/s3fwrn5_i2c.mod
