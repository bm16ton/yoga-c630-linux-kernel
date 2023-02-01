cmd_drivers/input/touchscreen/atmel_mxt_ts.mod := printf '%s\n'   atmel_mxt_ts.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/atmel_mxt_ts.mod
