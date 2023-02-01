cmd_drivers/nfc/microread/microread.mod := printf '%s\n'   microread.o | awk '!x[$$0]++ { print("drivers/nfc/microread/"$$0) }' > drivers/nfc/microread/microread.mod
