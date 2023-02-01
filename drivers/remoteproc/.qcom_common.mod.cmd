cmd_drivers/remoteproc/qcom_common.mod := printf '%s\n'   qcom_common.o | awk '!x[$$0]++ { print("drivers/remoteproc/"$$0) }' > drivers/remoteproc/qcom_common.mod
