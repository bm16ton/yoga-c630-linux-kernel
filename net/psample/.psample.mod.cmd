cmd_net/psample/psample.mod := printf '%s\n'   psample.o | awk '!x[$$0]++ { print("net/psample/"$$0) }' > net/psample/psample.mod
