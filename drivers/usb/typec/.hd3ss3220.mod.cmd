cmd_drivers/usb/typec/hd3ss3220.mod := printf '%s\n'   hd3ss3220.o | awk '!x[$$0]++ { print("drivers/usb/typec/"$$0) }' > drivers/usb/typec/hd3ss3220.mod
