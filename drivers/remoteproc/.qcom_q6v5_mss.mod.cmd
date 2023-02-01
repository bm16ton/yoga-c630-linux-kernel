cmd_drivers/remoteproc/qcom_q6v5_mss.mod := printf '%s\n'   qcom_q6v5_mss.o | awk '!x[$$0]++ { print("drivers/remoteproc/"$$0) }' > drivers/remoteproc/qcom_q6v5_mss.mod
