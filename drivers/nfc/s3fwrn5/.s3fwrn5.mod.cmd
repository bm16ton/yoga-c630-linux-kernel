cmd_drivers/nfc/s3fwrn5/s3fwrn5.mod := printf '%s\n'   core.o firmware.o nci.o phy_common.o | awk '!x[$$0]++ { print("drivers/nfc/s3fwrn5/"$$0) }' > drivers/nfc/s3fwrn5/s3fwrn5.mod
