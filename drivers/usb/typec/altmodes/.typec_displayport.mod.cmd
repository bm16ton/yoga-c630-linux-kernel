cmd_drivers/usb/typec/altmodes/typec_displayport.mod := printf '%s\n'   displayport.o | awk '!x[$$0]++ { print("drivers/usb/typec/altmodes/"$$0) }' > drivers/usb/typec/altmodes/typec_displayport.mod
