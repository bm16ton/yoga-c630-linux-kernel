cmd_drivers/nfc/nfcsim.mod := printf '%s\n'   nfcsim.o | awk '!x[$$0]++ { print("drivers/nfc/"$$0) }' > drivers/nfc/nfcsim.mod
