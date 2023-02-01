cmd_drivers/scsi/be2iscsi/be2iscsi.mod := printf '%s\n'   be_iscsi.o be_main.o be_mgmt.o be_cmds.o | awk '!x[$$0]++ { print("drivers/scsi/be2iscsi/"$$0) }' > drivers/scsi/be2iscsi/be2iscsi.mod
