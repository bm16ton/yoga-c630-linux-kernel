cmd_drivers/iio/light/noa1305.mod := printf '%s\n'   noa1305.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/noa1305.mod
