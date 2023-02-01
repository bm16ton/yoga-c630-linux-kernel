cmd_drivers/usb/serial/keyspan_pda.mod := printf '%s\n'   keyspan_pda.o | awk '!x[$$0]++ { print("drivers/usb/serial/"$$0) }' > drivers/usb/serial/keyspan_pda.mod
