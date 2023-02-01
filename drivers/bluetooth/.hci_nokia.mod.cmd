cmd_drivers/bluetooth/hci_nokia.mod := printf '%s\n'   hci_nokia.o | awk '!x[$$0]++ { print("drivers/bluetooth/"$$0) }' > drivers/bluetooth/hci_nokia.mod
