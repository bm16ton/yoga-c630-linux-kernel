cmd_drivers/scsi/iscsi_boot_sysfs.mod := printf '%s\n'   iscsi_boot_sysfs.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/iscsi_boot_sysfs.mod
