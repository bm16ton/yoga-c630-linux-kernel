cmd_drivers/iio/magnetometer/yamaha-yas530.mod := printf '%s\n'   yamaha-yas530.o | awk '!x[$$0]++ { print("drivers/iio/magnetometer/"$$0) }' > drivers/iio/magnetometer/yamaha-yas530.mod
