cmd_drivers/uio/uio_cif.mod := printf '%s\n'   uio_cif.o | awk '!x[$$0]++ { print("drivers/uio/"$$0) }' > drivers/uio/uio_cif.mod
