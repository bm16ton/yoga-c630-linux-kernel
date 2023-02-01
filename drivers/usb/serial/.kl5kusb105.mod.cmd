cmd_drivers/usb/serial/kl5kusb105.mod := printf '%s\n'   kl5kusb105.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/kl5kusb105.mod
