cmd_drivers/i2c/busses/i2c-pca-platform.mod := printf '%s\n'   i2c-pca-platform.o | awk '!x[$$0]++ { print("drivers/i2c/busses/"$$0) }' > drivers/i2c/busses/i2c-pca-platform.mod
