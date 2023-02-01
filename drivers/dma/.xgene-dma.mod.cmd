cmd_drivers/dma/xgene-dma.mod := printf '%s\n'   xgene-dma.o | awk '!x[$$0]++ { print("drivers/dma/"$$0) }' > drivers/dma/xgene-dma.mod
