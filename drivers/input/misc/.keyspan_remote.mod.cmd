cmd_drivers/input/misc/keyspan_remote.mod := printf '%s\n'   keyspan_remote.o | awk '!x[$$0]++ { print("drivers/input/misc/"$$0) }' > drivers/input/misc/keyspan_remote.mod
