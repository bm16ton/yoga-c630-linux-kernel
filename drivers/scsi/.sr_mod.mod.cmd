cmd_drivers/scsi/sr_mod.mod := printf '%s\n'   sr.o sr_ioctl.o sr_vendor.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/sr_mod.mod
