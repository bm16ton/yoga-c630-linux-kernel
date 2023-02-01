cmd_drivers/usb/chipidea/ci_hdrc_usb2.mod := printf '%s\n'   ci_hdrc_usb2.o | awk '!x[$$0]++ { print("drivers/usb/chipidea/"$$0) }' > drivers/usb/chipidea/ci_hdrc_usb2.mod
