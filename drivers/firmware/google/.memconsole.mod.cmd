cmd_drivers/firmware/google/memconsole.mod := printf '%s\n'   memconsole.o | awk '!x[$$0]++ { print("drivers/firmware/google/"$$0) }' > drivers/firmware/google/memconsole.mod
