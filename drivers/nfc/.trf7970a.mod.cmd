cmd_drivers/nfc/trf7970a.mod := printf '%s\n'   trf7970a.o | awk '!x[$$0]++ { print("drivers/nfc/"$$0) }' > drivers/nfc/trf7970a.mod
