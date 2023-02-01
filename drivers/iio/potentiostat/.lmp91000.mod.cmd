cmd_drivers/iio/potentiostat/lmp91000.mod := printf '%s\n'   lmp91000.o | awk '!x[$$0]++ { print("drivers/iio/potentiostat/"$$0) }' > drivers/iio/potentiostat/lmp91000.mod
