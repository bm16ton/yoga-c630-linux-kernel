cmd_drivers/iio/industrialio-triggered-event.mod := printf '%s\n'   industrialio-triggered-event.o | awk '!x[$$0]++ { print("drivers/iio/"$$0) }' > drivers/iio/industrialio-triggered-event.mod
