cmd_drivers/iio/humidity/hts221.mod := printf '%s\n'   hts221_core.o hts221_buffer.o | awk '!x[$$0]++ { print("drivers/iio/humidity/"$$0) }' > drivers/iio/humidity/hts221.mod
