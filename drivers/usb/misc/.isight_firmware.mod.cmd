cmd_drivers/usb/misc/isight_firmware.mod := printf '%s\n'   isight_firmware.o | awk '!x[$$0]++ { print("drivers/usb/misc/"$$0) }' > drivers/usb/misc/isight_firmware.mod
