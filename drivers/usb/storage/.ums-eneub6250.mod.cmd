cmd_drivers/usb/storage/ums-eneub6250.mod := printf '%s\n'   ene_ub6250.o | awk '!x[$$0]++ { print("drivers/usb/storage/"$$0) }' > drivers/usb/storage/ums-eneub6250.mod
