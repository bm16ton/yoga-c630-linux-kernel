cmd_drivers/iio/industrialio-sw-trigger.mod := printf '%s\n'   industrialio-sw-trigger.o | awk '!x[$$0]++ { print("drivers/iio/"$$0) }' > drivers/iio/industrialio-sw-trigger.mod
