cmd_drivers/hid/wacom.mod := printf '%s\n'   wacom_wac.o wacom_sys.o | awk '!x[$$0]++ { print("drivers/hid/"$$0) }' > drivers/hid/wacom.mod
