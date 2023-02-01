cmd_drivers/iio/pressure/icp10100.mod := printf '%s\n'   icp10100.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/icp10100.mod
