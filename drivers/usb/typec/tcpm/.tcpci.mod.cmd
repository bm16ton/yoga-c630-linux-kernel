cmd_drivers/usb/typec/tcpm/tcpci.mod := printf '%s\n'   tcpci.o | awk '!x[$$0]++ { print("drivers/usb/typec/tcpm/"$$0) }' > drivers/usb/typec/tcpm/tcpci.mod
