cmd_drivers/parport/parport.mod := printf '%s\n'   share.o ieee1284.o ieee1284_ops.o procfs.o daisy.o probe.o | awk '!x[$$0]++ { print("drivers/parport/"$$0) }' > drivers/parport/parport.mod
