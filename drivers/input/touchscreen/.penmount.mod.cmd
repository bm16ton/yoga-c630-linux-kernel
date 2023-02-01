cmd_drivers/input/touchscreen/penmount.mod := printf '%s\n'   penmount.o | awk '!x[$$0]++ { print("drivers/input/touchscreen/"$$0) }' > drivers/input/touchscreen/penmount.mod
