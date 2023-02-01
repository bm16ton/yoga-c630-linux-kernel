cmd_drivers/iio/pressure/abp060mg.mod := printf '%s\n'   abp060mg.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/abp060mg.mod
