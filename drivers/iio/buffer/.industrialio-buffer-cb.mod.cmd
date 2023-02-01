cmd_drivers/iio/buffer/industrialio-buffer-cb.mod := printf '%s\n'   industrialio-buffer-cb.o | awk '!x[$$0]++ { print("drivers/iio/buffer/"$$0) }' > drivers/iio/buffer/industrialio-buffer-cb.mod
