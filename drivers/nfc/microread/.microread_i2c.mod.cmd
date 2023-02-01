cmd_drivers/nfc/microread/microread_i2c.mod := printf '%s\n'   i2c.o | awk '!x[$$0]++ { print("drivers/nfc/microread/"$$0) }' > drivers/nfc/microread/microread_i2c.mod
