cmd_drivers/scsi/bnx2i/bnx2i.mod := printf '%s\n'   bnx2i_init.o bnx2i_hwi.o bnx2i_iscsi.o bnx2i_sysfs.o | awk '!x[$$0]++ { print("drivers/scsi/bnx2i/"$$0) }' > drivers/scsi/bnx2i/bnx2i.mod
