cmd_drivers/usb/typec/ucsi/ucsi_ccg.mod := printf '%s\n'   ucsi_ccg.o | awk '!x[$$0]++ { print("drivers/usb/typec/ucsi/"$$0) }' > drivers/usb/typec/ucsi/ucsi_ccg.mod
