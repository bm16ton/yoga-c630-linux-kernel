cmd_drivers/uio/uio_aec.mod := printf '%s\n'   uio_aec.o | awk '!x[$$0]++ { print("drivers/uio/"$$0) }' > drivers/uio/uio_aec.mod
