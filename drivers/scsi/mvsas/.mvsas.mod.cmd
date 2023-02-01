cmd_drivers/scsi/mvsas/mvsas.mod := printf '%s\n'   mv_init.o mv_sas.o mv_64xx.o mv_94xx.o | awk '!x[$$0]++ { print("drivers/scsi/mvsas/"$$0) }' > drivers/scsi/mvsas/mvsas.mod
