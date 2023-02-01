cmd_drivers/xen/xen-gntdev.mod := printf '%s\n'   gntdev.o | awk '!x[$$0]++ { print("drivers/xen/"$$0) }' > drivers/xen/xen-gntdev.mod
