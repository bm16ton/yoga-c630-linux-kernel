cmd_drivers/usb/musb/sunxi.mod := printf '%s\n'   sunxi.o | awk '!x[$$0]++ { print("drivers/usb/musb/"$$0) }' > drivers/usb/musb/sunxi.mod
