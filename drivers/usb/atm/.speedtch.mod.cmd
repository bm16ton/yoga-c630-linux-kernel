cmd_drivers/usb/atm/speedtch.mod := printf '%s\n'   speedtch.o | awk '!x[$$0]++ { print("drivers/usb/atm/"$$0) }' > drivers/usb/atm/speedtch.mod
