cmd_drivers/usb/typec/tcpm/tcpci_rt1711h.mod := printf '%s\n'   tcpci_rt1711h.o | awk '!x[$$0]++ { print("drivers/usb/typec/tcpm/"$$0) }' > drivers/usb/typec/tcpm/tcpci_rt1711h.mod
