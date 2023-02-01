cmd_drivers/remoteproc/qcom_pil_info.mod := printf '%s\n'   qcom_pil_info.o | awk '!x[$$0]++ { print("drivers/remoteproc/"$$0) }' > drivers/remoteproc/qcom_pil_info.mod
