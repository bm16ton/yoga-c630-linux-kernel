cmd_drivers/xen/xenfs/xenfs.mod := printf '%s\n'   super.o xenstored.o | awk '!x[$$0]++ { print("drivers/xen/xenfs/"$$0) }' > drivers/xen/xenfs/xenfs.mod
