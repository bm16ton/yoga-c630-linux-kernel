cmd_drivers/uio/uio_dmem_genirq.mod := printf '%s\n'   uio_dmem_genirq.o | awk '!x[$$0]++ { print("drivers/uio/"$$0) }' > drivers/uio/uio_dmem_genirq.mod
