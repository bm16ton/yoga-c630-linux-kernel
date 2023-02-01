cmd_drivers/iio/temperature/mlx90632.mod := printf '%s\n'   mlx90632.o | awk '!x[$$0]++ { print("drivers/iio/temperature/"$$0) }' > drivers/iio/temperature/mlx90632.mod
