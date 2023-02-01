cmd_drivers/misc/cb710/cb710.mod := printf '%s\n'   core.o sgbuf2.o | awk '!x[$$0]++ { print("drivers/misc/cb710/"$$0) }' > drivers/misc/cb710/cb710.mod
