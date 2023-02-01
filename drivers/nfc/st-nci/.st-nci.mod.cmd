cmd_drivers/nfc/st-nci/st-nci.mod := printf '%s\n'   ndlc.o core.o se.o vendor_cmds.o | awk '!x[$$0]++ { print("drivers/nfc/st-nci/"$$0) }' > drivers/nfc/st-nci/st-nci.mod
