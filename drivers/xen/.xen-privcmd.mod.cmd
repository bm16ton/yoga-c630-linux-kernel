cmd_drivers/xen/xen-privcmd.mod := printf '%s\n'   privcmd.o privcmd-buf.o | awk '!x[$$0]++ { print("drivers/xen/"$$0) }' > drivers/xen/xen-privcmd.mod
