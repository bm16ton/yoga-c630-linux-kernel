cmd_drivers/nfc/pn533/pn533.mod := printf '%s\n'   pn533.o | awk '!x[$$0]++ { print("drivers/nfc/pn533/"$$0) }' > drivers/nfc/pn533/pn533.mod
