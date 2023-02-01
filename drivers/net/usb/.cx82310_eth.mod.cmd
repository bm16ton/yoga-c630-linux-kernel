cmd_drivers/net/usb/cx82310_eth.mod := printf '%s\n'   cx82310_eth.o | awk '!x[$$0]++ { print("drivers/net/usb/"$$0) }' > drivers/net/usb/cx82310_eth.mod
