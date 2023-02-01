cmd_drivers/block/zram/zram.mod := printf '%s\n'   zcomp.o zram_drv.o | awk '!x[$$0]++ { print("drivers/block/zram/"$$0) }' > drivers/block/zram/zram.mod
