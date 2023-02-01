cmd_drivers/uio/uio_sercos3.mod := printf '%s\n'   uio_sercos3.o | awk '!x[$$0]++ { print("drivers/uio/"$$0) }' > drivers/uio/uio_sercos3.mod
