cmd_drivers/net/wireless/ralink/rt2x00/rt73usb.mod := printf '%s\n'   rt73usb.o | awk '!x[$$0]++ { print("drivers/net/wireless/ralink/rt2x00/"$$0) }' > drivers/net/wireless/ralink/rt2x00/rt73usb.mod
