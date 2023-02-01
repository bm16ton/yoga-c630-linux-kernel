cmd_drivers/input/touchscreen/mcs5000_ts.mod := printf '%s\n'   mcs5000_ts.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/mcs5000_ts.mod
