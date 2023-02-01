cmd_drivers/usb/chipidea/ci_hdrc_pci.mod := printf '%s\n'   ci_hdrc_pci.o | awk '!x[$$0]++ { print("drivers/usb/chipidea/"$$0) }' > drivers/usb/chipidea/ci_hdrc_pci.mod
