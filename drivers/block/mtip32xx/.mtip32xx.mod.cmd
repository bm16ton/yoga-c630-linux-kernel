cmd_drivers/block/mtip32xx/mtip32xx.mod := printf '%s\n'   mtip32xx.o | awk '!x[$$0]++ { print("drivers/block/mtip32xx/"$$0) }' > drivers/block/mtip32xx/mtip32xx.mod
