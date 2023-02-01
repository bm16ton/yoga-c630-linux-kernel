cmd_drivers/dma/qcom/hdma.mod := printf '%s\n'   hidma_ll.o hidma.o hidma_dbg.o | awk '!x[$$0]++ { print("drivers/dma/qcom/"$$0) }' > drivers/dma/qcom/hdma.mod
