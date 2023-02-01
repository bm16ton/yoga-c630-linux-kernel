cmd_drivers/iio/trigger/iio-trig-interrupt.mod := printf '%s\n'   iio-trig-interrupt.o | awk '!x[$$0]++ { print("drivers/iio/trigger/"$$0) }' > drivers/iio/trigger/iio-trig-interrupt.mod
