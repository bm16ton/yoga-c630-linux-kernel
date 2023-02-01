cmd_drivers/i2c/busses/i2c-tiny-usb.mod := printf '%s\n'   i2c-tiny-usb.o | awk '!x[$$0]++ { print("drivers/i2c/busses/"$$0) }' > drivers/i2c/busses/i2c-tiny-usb.mod
