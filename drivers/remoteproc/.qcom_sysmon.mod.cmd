cmd_drivers/remoteproc/qcom_sysmon.mod := printf '%s\n'   qcom_sysmon.o | awk '!x[$$0]++ { print("drivers/remoteproc/"$$0) }' > drivers/remoteproc/qcom_sysmon.mod
