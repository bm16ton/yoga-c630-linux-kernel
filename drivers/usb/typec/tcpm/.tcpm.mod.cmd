cmd_drivers/usb/typec/tcpm/tcpm.mod := printf '%s\n'   tcpm.o | awk '!x[$$0]++ { print("drivers/usb/typec/tcpm/"$$0) }' > drivers/usb/typec/tcpm/tcpm.mod
