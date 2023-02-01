cmd_drivers/iio/trigger/iio-trig-sysfs.mod := printf '%s\n'   iio-trig-sysfs.o | awk '!x[$$0]++ { print("drivers/iio/trigger/"$$0) }' > drivers/iio/trigger/iio-trig-sysfs.mod
