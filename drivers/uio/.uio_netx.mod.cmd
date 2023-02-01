cmd_drivers/uio/uio_netx.mod := printf '%s\n'   uio_netx.o | awk '!x[$$0]++ { print("drivers/uio/"$$0) }' > drivers/uio/uio_netx.mod
