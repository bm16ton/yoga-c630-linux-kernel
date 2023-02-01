cmd_drivers/i2c/busses/i2c-xgene-slimpro.mod := printf '%s\n'   i2c-xgene-slimpro.o | awk '!x[$$0]++ { print("drivers/i2c/busses/"$$0) }' > drivers/i2c/busses/i2c-xgene-slimpro.mod
