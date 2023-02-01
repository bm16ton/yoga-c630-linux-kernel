cmd_drivers/uio/uio.mod := printf '%s\n'   uio.o | awk '!x[$$0]++ { print("drivers/uio/"$$0) }' > drivers/uio/uio.mod
