cmd_drivers/usb/isp1760/isp1760.mod := printf '%s\n'   isp1760-core.o isp1760-if.o isp1760-hcd.o isp1760-udc.o | awk '!x[$$0]++ { print("drivers/usb/isp1760/"$$0) }' > drivers/usb/isp1760/isp1760.mod
