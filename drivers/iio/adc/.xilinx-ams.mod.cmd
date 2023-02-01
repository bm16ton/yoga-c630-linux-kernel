cmd_drivers/iio/adc/xilinx-ams.mod := printf '%s\n'   xilinx-ams.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/xilinx-ams.mod
