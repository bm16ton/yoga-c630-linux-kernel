cmd_net/atm/atm.mod := printf '%s\n'   addr.o pvc.o signaling.o svc.o ioctl.o common.o atm_misc.o raw.o resources.o atm_sysfs.o proc.o | awk '!x[$$0]++ { print("net/atm/"$$0) }' > net/atm/atm.mod
