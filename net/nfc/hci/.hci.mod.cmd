cmd_net/nfc/hci/hci.mod := printf '%s\n'   core.o hcp.o command.o llc.o llc_nop.o llc_shdlc.o | awk '!x[$$0]++ { print("net/nfc/hci/"$$0) }' > net/nfc/hci/hci.mod
