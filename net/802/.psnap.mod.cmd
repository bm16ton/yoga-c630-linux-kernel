cmd_net/802/psnap.mod := printf '%s\n'   psnap.o | awk '!x[$$0]++ { print("net/802/"$$0) }' > net/802/psnap.mod
