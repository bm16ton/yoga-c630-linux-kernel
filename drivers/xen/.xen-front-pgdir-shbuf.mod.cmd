cmd_drivers/xen/xen-front-pgdir-shbuf.mod := printf '%s\n'   xen-front-pgdir-shbuf.o | awk '!x[$$0]++ { print("drivers/xen/"$$0) }' > drivers/xen/xen-front-pgdir-shbuf.mod
