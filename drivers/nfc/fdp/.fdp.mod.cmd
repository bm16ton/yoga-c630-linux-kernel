cmd_drivers/nfc/fdp/fdp.mod := printf '%s\n'   fdp.o | awk '!x[$$0]++ { print("drivers/nfc/fdp/"$$0) }' > drivers/nfc/fdp/fdp.mod
