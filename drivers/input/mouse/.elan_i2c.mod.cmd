cmd_drivers/input/mouse/elan_i2c.mod := printf '%s\n'   elan_i2c_core.o elan_i2c_i2c.o | awk '!x[$$0]++ { print("drivers/input/mouse/"$$0) }' > drivers/input/mouse/elan_i2c.mod
