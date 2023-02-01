cmd_net/802/stp.mod := printf '%s\n'   stp.o | awk '!x[$$0]++ { print("net/802/"$$0) }' > net/802/stp.mod
