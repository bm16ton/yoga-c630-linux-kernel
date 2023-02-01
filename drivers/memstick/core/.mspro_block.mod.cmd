cmd_drivers/memstick/core/mspro_block.mod := printf '%s\n'   mspro_block.o | awk '!x[$$0]++ { print("drivers/memstick/core/"$$0) }' > drivers/memstick/core/mspro_block.mod
