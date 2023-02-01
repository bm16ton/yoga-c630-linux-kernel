cmd_drivers/uio/uio_mf624.mod := printf '%s\n'   uio_mf624.o | awk '!x[$$0]++ { print("drivers/uio/"$$0) }' > drivers/uio/uio_mf624.mod
