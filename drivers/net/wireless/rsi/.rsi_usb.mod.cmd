cmd_drivers/net/wireless/rsi/rsi_usb.mod := printf '%s\n'   rsi_91x_usb.o rsi_91x_usb_ops.o | awk '!x[$$0]++ { print("drivers/net/wireless/rsi/"$$0) }' > drivers/net/wireless/rsi/rsi_usb.mod
