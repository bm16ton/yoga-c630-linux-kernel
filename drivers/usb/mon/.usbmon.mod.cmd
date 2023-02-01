cmd_drivers/usb/mon/usbmon.mod := printf '%s\n'   mon_main.o mon_stat.o mon_text.o mon_bin.o | awk '!x[$$0]++ { print("drivers/usb/mon/"$$0) }' > drivers/usb/mon/usbmon.mod
