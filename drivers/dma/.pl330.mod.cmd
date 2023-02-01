cmd_drivers/dma/pl330.mod := printf '%s\n'   pl330.o | awk '!x[$$0]++ { print("drivers/dma/"$$0) }' > drivers/dma/pl330.mod
