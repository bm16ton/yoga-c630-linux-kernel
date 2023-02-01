cmd_drivers/mtd/nftl.mod := printf '%s\n'   nftlcore.o nftlmount.o | awk '!x[$$0]++ { print("drivers/mtd/"$$0) }' > drivers/mtd/nftl.mod
