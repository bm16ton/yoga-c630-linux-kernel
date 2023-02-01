cmd_drivers/xen/xen-scsiback.mod := printf '%s\n'   xen-scsiback.o | awk '!x[$$0]++ { print("drivers/xen/"$$0) }' > drivers/xen/xen-scsiback.mod
