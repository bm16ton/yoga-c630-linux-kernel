cmd_drivers/input/mouse/synaptics_i2c.mod := printf '%s\n'   synaptics_i2c.o | awk '!x[$$0]++ { print("drivers/input/mouse/"$$0) }' > drivers/input/mouse/synaptics_i2c.mod
