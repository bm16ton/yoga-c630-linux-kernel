cmd_drivers/nfc/pn544/pn544.mod := printf '%s\n'   pn544.o | awk '!x[$$0]++ { print("drivers/nfc/pn544/"$$0) }' > drivers/nfc/pn544/pn544.mod
