cmd_drivers/iio/amplifiers/ada4250.mod := printf '%s\n'   ada4250.o | awk '!x[$$0]++ { print("drivers/iio/amplifiers/"$$0) }' > drivers/iio/amplifiers/ada4250.mod
