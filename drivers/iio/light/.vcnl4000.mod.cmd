cmd_drivers/iio/light/vcnl4000.mod := printf '%s\n'   vcnl4000.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/vcnl4000.mod
