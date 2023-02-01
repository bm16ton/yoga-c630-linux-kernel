cmd_drivers/net/usb/rndis_host.mod := printf '%s\n'   rndis_host.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/rndis_host.mod
