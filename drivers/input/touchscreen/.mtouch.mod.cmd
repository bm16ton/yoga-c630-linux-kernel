cmd_drivers/input/touchscreen/mtouch.mod := printf '%s\n'   mtouch.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/mtouch.mod
