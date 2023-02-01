cmd_drivers/iio/light/us5182d.mod := printf '%s\n'   us5182d.o | awk '!x[$$0]++ { print("drivers/iio/light/"$$0) }' > drivers/iio/light/us5182d.mod
