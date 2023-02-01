cmd_drivers/scsi/qla2xxx/tcm_qla2xxx.mod := printf '%s\n'   tcm_qla2xxx.o | awk '!x[$$0]++ { print("drivers/scsi/qla2xxx/"$$0) }' > drivers/scsi/qla2xxx/tcm_qla2xxx.mod
