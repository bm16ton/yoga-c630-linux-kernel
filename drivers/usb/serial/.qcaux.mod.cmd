cmd_drivers/usb/serial/qcaux.mod := printf '%s\n'   qcaux.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/qcaux.mod
