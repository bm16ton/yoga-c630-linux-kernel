cmd_drivers/usb/typec/tcpm/tcpci_maxim.mod := printf '%s\n'   tcpci_maxim.o | awk '!x[$$0]++ { print("drivers/usb/typec/tcpm/"$$0) }' > drivers/usb/typec/tcpm/tcpci_maxim.mod
