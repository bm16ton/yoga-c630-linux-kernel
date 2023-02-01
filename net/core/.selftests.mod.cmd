cmd_net/core/selftests.mod := printf '%s\n'   selftests.o | awk '!x[$$0]++ { print("net/core/"$$0) }' > net/core/selftests.mod
