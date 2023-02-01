cmd_drivers/scsi/cxgbi/cxgb3i/cxgb3i.mod := printf '%s\n'   cxgb3i.o | awk '!x[$$0]++ { print("drivers/scsi/cxgbi/cxgb3i/"$$0) }' > drivers/scsi/cxgbi/cxgb3i/cxgb3i.mod
