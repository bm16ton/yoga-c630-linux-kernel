cmd_drivers/memstick/host/r592.mod := printf '%s\n'   r592.o | awk '!x[$$0]++ { print("drivers/memstick/host/"$$0) }' > drivers/memstick/host/r592.mod
