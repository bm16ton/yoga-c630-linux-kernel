cmd_drivers/vfio/vfio.mod := printf '%s\n'   vfio_main.o iova_bitmap.o container.o | awk '!x[$$0]++ { print("drivers/vfio/"$$0) }' > drivers/vfio/vfio.mod
