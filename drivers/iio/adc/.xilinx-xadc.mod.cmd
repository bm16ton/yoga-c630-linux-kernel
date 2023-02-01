cmd_drivers/iio/adc/xilinx-xadc.mod := printf '%s\n'   xilinx-xadc-core.o xilinx-xadc-events.o | awk '!x[$$0]++ { print("drivers/iio/adc/"$$0) }' > drivers/iio/adc/xilinx-xadc.mod
