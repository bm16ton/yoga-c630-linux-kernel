cmd_drivers/scsi/hisi_sas/hisi_sas_main.mod := printf '%s\n'   hisi_sas_main.o | awk '!x[$$0]++ { print("drivers/scsi/hisi_sas/"$$0) }' > drivers/scsi/hisi_sas/hisi_sas_main.mod
