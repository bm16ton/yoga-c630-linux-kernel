cmd_drivers/iio/proximity/vcnl3020.mod := printf '%s\n'   vcnl3020.o | awk '!x[$$0]++ { print("drivers/iio/proximity/"$$0) }' > drivers/iio/proximity/vcnl3020.mod
