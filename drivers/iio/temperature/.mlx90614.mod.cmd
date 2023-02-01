cmd_drivers/iio/temperature/mlx90614.mod := printf '%s\n'   mlx90614.o | awk '!x[$$0]++ { print("drivers/iio/temperature/"$$0) }' > drivers/iio/temperature/mlx90614.mod
