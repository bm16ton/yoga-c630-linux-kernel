cmd_drivers/usb/chipidea/usbmisc_imx.mod := printf '%s\n'   usbmisc_imx.o | awk '!x[$$0]++ { print("drivers/usb/chipidea/"$$0) }' > drivers/usb/chipidea/usbmisc_imx.mod
