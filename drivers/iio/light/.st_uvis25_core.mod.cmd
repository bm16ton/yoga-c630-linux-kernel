cmd_drivers/iio/light/st_uvis25_core.mod := printf '%s\n'   st_uvis25_core.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/st_uvis25_core.mod
