cmd_drivers/dma/fsl-qdma.mod := printf '%s\n'   fsl-qdma.o | awk '!x[$$0]++ { print("drivers/dma/"$$0) }' > drivers/dma/fsl-qdma.mod
