cmd_drivers/memstick/core/memstick.mod := printf '%s\n'   memstick.o | awk '!x[$$0]++ { print("drivers/memstick/core/"$$0) }' > drivers/memstick/core/memstick.mod
