cmd_net/802/p8022.mod := printf '%s\n'   p8022.o | awk '!x[$$0]++ { print("net/802/"$$0) }' > net/802/p8022.mod
