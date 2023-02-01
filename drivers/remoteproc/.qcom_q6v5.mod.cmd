cmd_drivers/remoteproc/qcom_q6v5.mod := printf '%s\n'   qcom_q6v5.o | awk '!x[$$0]++ { print("drivers/remoteproc/"$$0) }' > drivers/remoteproc/qcom_q6v5.mod
