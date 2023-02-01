cmd_drivers/i2c/busses/i2c-cros-ec-tunnel.mod := printf '%s\n'   i2c-cros-ec-tunnel.o | awk '!x[$$0]++ { print("drivers/i2c/busses/"$$0) }' > drivers/i2c/busses/i2c-cros-ec-tunnel.mod
