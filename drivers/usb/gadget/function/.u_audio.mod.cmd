cmd_drivers/usb/gadget/function/u_audio.mod := printf '%s\n'   u_audio.o | awk '!x[$$0]++ { print("drivers/usb/gadget/function/"$$0) }' > drivers/usb/gadget/function/u_audio.mod
