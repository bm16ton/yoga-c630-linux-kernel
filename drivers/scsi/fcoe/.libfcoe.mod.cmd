cmd_drivers/scsi/fcoe/libfcoe.mod := printf '%s\n'   fcoe_ctlr.o fcoe_transport.o fcoe_sysfs.o | awk '!x[$$0]++ { print("drivers/scsi/fcoe/"$$0) }' > drivers/scsi/fcoe/libfcoe.mod
