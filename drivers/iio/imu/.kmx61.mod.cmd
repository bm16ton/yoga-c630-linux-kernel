cmd_drivers/iio/imu/kmx61.mod := printf '%s\n'   kmx61.o | awk '!x[$$0]++ { print("drivers/iio/imu/"$$0) }' > drivers/iio/imu/kmx61.mod
