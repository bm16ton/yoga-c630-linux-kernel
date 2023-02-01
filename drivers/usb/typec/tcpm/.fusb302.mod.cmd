cmd_drivers/usb/typec/tcpm/fusb302.mod := printf '%s\n'   fusb302.o | awk '!x[$$0]++ { print("drivers/usb/typec/tcpm/"$$0) }' > drivers/usb/typec/tcpm/fusb302.mod
