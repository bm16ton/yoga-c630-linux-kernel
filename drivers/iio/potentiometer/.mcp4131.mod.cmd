cmd_drivers/iio/potentiometer/mcp4131.mod := printf '%s\n'   mcp4131.o | awk '!x[$$0]++ { print("drivers/iio/potentiometer/"$$0) }' > drivers/iio/potentiometer/mcp4131.mod
