cmd_drivers/hid/hid-logitech.mod := printf '%s\n'   hid-lg.o hid-lgff.o hid-lg2ff.o hid-lg3ff.o hid-lg4ff.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-logitech.mod
