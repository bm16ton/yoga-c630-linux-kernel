cmd_drivers/block/xen-blkfront.mod := printf '%s\n'   xen-blkfront.o | awk '!x[$$0]++ { print("drivers/block/"$$0) }' > drivers/block/xen-blkfront.mod
