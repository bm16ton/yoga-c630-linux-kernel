cmd_drivers/scsi/cxgbi/libcxgbi.mod := printf '%s\n'   libcxgbi.o | awk '!x[$$0]++ { print("drivers/scsi/cxgbi/"$$0) }' > drivers/scsi/cxgbi/libcxgbi.mod
