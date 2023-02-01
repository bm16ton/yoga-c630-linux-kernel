cmd_drivers/nfc/port100.mod := printf '%s\n'   port100.o | awk '!x[$$0]++ { print("drivers/nfc/"$$0) }' > drivers/nfc/port100.mod
