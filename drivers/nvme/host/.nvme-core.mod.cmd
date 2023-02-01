cmd_drivers/nvme/host/nvme-core.mod := printf '%s\n'   core.o ioctl.o trace.o multipath.o zns.o hwmon.o | awk '!x[$$0]++ { print("drivers/nvme/host/"$$0) }' > drivers/nvme/host/nvme-core.mod
