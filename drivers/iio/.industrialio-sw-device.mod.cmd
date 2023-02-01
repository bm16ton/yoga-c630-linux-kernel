cmd_drivers/iio/industrialio-sw-device.mod := printf '%s\n'   industrialio-sw-device.o | awk '!x[$$0]++ { print("drivers/iio/"$$0) }' > drivers/iio/industrialio-sw-device.mod
