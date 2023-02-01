cmd_drivers/xen/xen-gntalloc.mod := printf '%s\n'   gntalloc.o | awk '!x[$$0]++ { print("drivers/xen/"$$0) }' > drivers/xen/xen-gntalloc.mod
