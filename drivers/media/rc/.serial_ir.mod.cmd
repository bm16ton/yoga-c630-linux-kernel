cmd_drivers/media/rc/serial_ir.mod := printf '%s\n'   serial_ir.o | awk '!x[$$0]++ { print("drivers/media/rc/"$$0) }' > drivers/media/rc/serial_ir.mod
