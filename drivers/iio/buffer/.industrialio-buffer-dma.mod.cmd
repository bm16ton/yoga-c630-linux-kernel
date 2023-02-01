cmd_drivers/iio/buffer/industrialio-buffer-dma.mod := printf '%s\n'   industrialio-buffer-dma.o | awk '!x[$$0]++ { print("drivers/iio/buffer/"$$0) }' > drivers/iio/buffer/industrialio-buffer-dma.mod
