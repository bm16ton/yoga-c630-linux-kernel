cmd_drivers/iio/light/vcnl4035.mod := printf '%s\n'   vcnl4035.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/vcnl4035.mod
