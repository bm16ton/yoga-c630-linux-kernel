cmd_drivers/soc/qcom/rmtfs_mem.mod := printf '%s\n'   rmtfs_mem.o | awk '!x[$$0]++ { print("drivers/soc/qcom/"$$0) }' > drivers/soc/qcom/rmtfs_mem.mod
