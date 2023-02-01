cmd_drivers/net/usb/qmi_wwan.mod := printf '%s\n'   qmi_wwan.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/qmi_wwan.mod
