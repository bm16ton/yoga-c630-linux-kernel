cmd_net/nfc/nci/nci.mod := printf '%s\n'   core.o data.o lib.o ntf.o rsp.o hci.o | awk '!x[$$0]++ { print("net/nfc/nci/"$$0) }' > net/nfc/nci/nci.mod
