cmd_drivers/uio/uio_pdrv_genirq.mod := printf '%s\n'   uio_pdrv_genirq.o | awk '!x[$$0]++ { print("drivers/uio/"$$0) }' > drivers/uio/uio_pdrv_genirq.mod
