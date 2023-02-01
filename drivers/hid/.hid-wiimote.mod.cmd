cmd_drivers/hid/hid-wiimote.mod := printf '%s\n'   hid-wiimote-core.o hid-wiimote-modules.o hid-wiimote-debug.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/hid-wiimote.mod
