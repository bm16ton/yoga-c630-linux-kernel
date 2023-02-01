cmd_drivers/dma/k3dma.mod := printf '%s\n'   k3dma.o | awk '!x[$$0]++ { print("drivers/dma/"$$0) }' > drivers/dma/k3dma.mod
