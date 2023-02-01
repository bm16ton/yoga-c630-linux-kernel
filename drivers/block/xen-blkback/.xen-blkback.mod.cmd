cmd_drivers/block/xen-blkback/xen-blkback.mod := printf '%s\n'   blkback.o xenbus.o | awk '!x[$$0]++ { print("drivers/block/xen-blkback/"$$0) }' > drivers/block/xen-blkback/xen-blkback.mod
