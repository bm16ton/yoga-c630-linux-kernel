cmd_drivers/media/i2c/sony-btf-mpx.mod := printf '%s\n'   sony-btf-mpx.o | awk '!x[$$0]++ { print("drivers/media/i2c/"$$0) }' > drivers/media/i2c/sony-btf-mpx.mod
