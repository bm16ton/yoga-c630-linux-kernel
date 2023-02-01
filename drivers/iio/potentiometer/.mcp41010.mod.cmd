cmd_drivers/iio/potentiometer/mcp41010.mod := printf '%s\n'   mcp41010.o | awk '!x[$$0]++ { print("drivers/iio/potentiometer/"$$0) }' > drivers/iio/potentiometer/mcp41010.mod
