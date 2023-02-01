cmd_drivers/dax/device_dax.mod := printf '%s\n'   device.o | awk '!x[$$0]++ { print("drivers/dax/"$$0) }' > drivers/dax/device_dax.mod
