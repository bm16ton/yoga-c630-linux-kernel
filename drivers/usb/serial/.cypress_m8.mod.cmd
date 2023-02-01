cmd_drivers/usb/serial/cypress_m8.mod := printf '%s\n'   cypress_m8.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/cypress_m8.mod
