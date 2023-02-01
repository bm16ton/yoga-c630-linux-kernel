cmd_drivers/scsi/cxgbi/cxgb4i/cxgb4i.mod := printf '%s\n'   cxgb4i.o | awk '!x[$$0]++ { print("drivers/scsi/cxgbi/cxgb4i/"$$0) }' > drivers/scsi/cxgbi/cxgb4i/cxgb4i.mod
