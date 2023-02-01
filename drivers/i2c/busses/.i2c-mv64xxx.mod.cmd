cmd_drivers/i2c/busses/i2c-mv64xxx.mod := printf '%s\n'   i2c-mv64xxx.o | awk '!x[$$0]++ { print("drivers/i2c/busses/"$$0) }' > drivers/i2c/busses/i2c-mv64xxx.mod
