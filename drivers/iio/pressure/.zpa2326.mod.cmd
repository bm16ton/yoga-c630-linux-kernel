cmd_drivers/iio/pressure/zpa2326.mod := printf '%s\n'   zpa2326.o | awk '!x[$$0]++ { print("drivers/iio/pressure/"$$0) }' > drivers/iio/pressure/zpa2326.mod
