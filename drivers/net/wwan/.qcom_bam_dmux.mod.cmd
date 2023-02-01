cmd_drivers/net/wwan/qcom_bam_dmux.mod := printf '%s\n'   qcom_bam_dmux.o | awk '!x[$$0]++ { print("drivers/net/wwan/"$$0) }' > drivers/net/wwan/qcom_bam_dmux.mod
