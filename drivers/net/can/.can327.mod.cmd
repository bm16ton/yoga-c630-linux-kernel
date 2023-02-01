cmd_drivers/net/can/can327.mod := printf '%s\n'   can327.o | awk '!x[$$0]++ { print("drivers/net/can/"$$0) }' > drivers/net/can/can327.mod
