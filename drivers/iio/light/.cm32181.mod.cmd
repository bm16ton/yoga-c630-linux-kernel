cmd_drivers/iio/light/cm32181.mod := printf '%s\n'   cm32181.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/cm32181.mod
