cmd_drivers/scsi/st.mod := printf '%s\n'   st.o | awk '!x[$$0]++ { print("drivers/scsi/"$$0) }' > drivers/scsi/st.mod
