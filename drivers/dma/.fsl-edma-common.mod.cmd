cmd_drivers/dma/fsl-edma-common.mod := printf '%s\n'   fsl-edma-common.o | awk '!x[$$0]++ { print("drivers/dma/"$$0) }' > drivers/dma/fsl-edma-common.mod
