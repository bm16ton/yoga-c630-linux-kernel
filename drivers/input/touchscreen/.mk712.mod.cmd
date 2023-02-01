cmd_drivers/input/touchscreen/mk712.mod := printf '%s\n'   mk712.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/mk712.mod
