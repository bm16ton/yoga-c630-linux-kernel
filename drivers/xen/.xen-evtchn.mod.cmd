cmd_drivers/xen/xen-evtchn.mod := printf '%s\n'   evtchn.o | awk '!x[$$0]++ { print("drivers/xen/"$$0) }' > drivers/xen/xen-evtchn.mod
