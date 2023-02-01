cmd_drivers/input/touchscreen/eeti_ts.mod := printf '%s\n'   eeti_ts.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/eeti_ts.mod
