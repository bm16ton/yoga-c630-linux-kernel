cmd_drivers/dma/qcom/hdma_mgmt.mod := printf '%s\n'   hidma_mgmt.o hidma_mgmt_sys.o | awk '!x[$$0]++ { print("drivers/dma/qcom/"$$0) }' > drivers/dma/qcom/hdma_mgmt.mod
