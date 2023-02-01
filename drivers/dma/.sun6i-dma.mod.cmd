cmd_drivers/dma/sun6i-dma.mod := printf '%s\n'   sun6i-dma.o | awk '!x[$$0]++ { print("drivers/dma/"$$0) }' > drivers/dma/sun6i-dma.mod
