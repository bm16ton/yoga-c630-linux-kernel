cmd_drivers/vfio/vfio_virqfd.mod := printf '%s\n'   virqfd.o | awk '!x[$$0]++ { print("drivers/vfio/"$$0) }' > drivers/vfio/vfio_virqfd.mod
