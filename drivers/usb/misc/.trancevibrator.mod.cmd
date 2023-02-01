cmd_drivers/usb/misc/trancevibrator.mod := printf '%s\n'   trancevibrator.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/trancevibrator.mod
