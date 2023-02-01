cmd_drivers/dma/fsl-edma.mod := printf '%s\n'   fsl-edma.o | awk '!x[$$0]++ { print("drivers/dma/"$$0) }' > drivers/dma/fsl-edma.mod
