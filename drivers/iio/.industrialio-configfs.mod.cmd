cmd_drivers/iio/industrialio-configfs.mod := printf '%s\n'   industrialio-configfs.o | awk '!x[$$0]++ { print("drivers/iio/"$$0) }' > drivers/iio/industrialio-configfs.mod
