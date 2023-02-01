cmd_drivers/scsi/hisi_sas/hisi_sas_v1_hw.mod := printf '%s\n'   hisi_sas_v1_hw.o | awk '!x[$$0]++ { print("drivers/scsi/hisi_sas/"$$0) }' > drivers/scsi/hisi_sas/hisi_sas_v1_hw.mod
