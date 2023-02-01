cmd_drivers/nfc/st21nfca/st21nfca_hci.mod := printf '%s\n'   core.o dep.o se.o vendor_cmds.o | awk '!x[$$0]++ { print("drivers/nfc/st21nfca/"$$0) }' > drivers/nfc/st21nfca/st21nfca_hci.mod
