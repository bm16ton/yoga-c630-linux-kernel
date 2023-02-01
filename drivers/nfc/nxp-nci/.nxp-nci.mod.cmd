cmd_drivers/nfc/nxp-nci/nxp-nci.mod := printf '%s\n'   core.o firmware.o | awk '!x[$$0]++ { print("drivers/nfc/nxp-nci/"$$0) }' > drivers/nfc/nxp-nci/nxp-nci.mod
