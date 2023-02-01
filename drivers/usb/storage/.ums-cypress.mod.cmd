cmd_drivers/usb/storage/ums-cypress.mod := printf '%s\n'   cypress_atacb.o | awk '!x[$$0]++ { print("drivers/usb/storage/"$$0) }' > drivers/usb/storage/ums-cypress.mod
