cmd_drivers/iio/potentiometer/mcp4018.mod := printf '%s\n'   mcp4018.o | awk '!x[$$0]++ { print("drivers/iio/potentiometer/"$$0) }' > drivers/iio/potentiometer/mcp4018.mod
