cmd_drivers/iio/buffer/kfifo_buf.mod := printf '%s\n'   kfifo_buf.o | awk '!x[$$0]++ { print("drivers/iio/buffer/"$$0) }' > drivers/iio/buffer/kfifo_buf.mod
