cmd_drivers/usb/typec/altmodes/typec_nvidia.mod := printf '%s\n'   nvidia.o | awk '!x[$$0]++ { print("drivers/usb/typec/altmodes/"$$0) }' > drivers/usb/typec/altmodes/typec_nvidia.mod
