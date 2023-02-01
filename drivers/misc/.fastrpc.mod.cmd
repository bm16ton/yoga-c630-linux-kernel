cmd_drivers/misc/fastrpc.mod := printf '%s\n'   fastrpc.o | awk '!x[$$0]++ { print("drivers/misc/"$$0) }' > drivers/misc/fastrpc.mod
