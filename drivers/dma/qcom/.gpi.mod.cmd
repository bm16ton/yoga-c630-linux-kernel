cmd_drivers/dma/qcom/gpi.mod := printf '%s\n'   gpi.o | awk '!x[$$0]++ { print("drivers/dma/qcom/"$$0) }' > drivers/dma/qcom/gpi.mod
