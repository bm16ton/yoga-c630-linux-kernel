cmd_net/ife/ife.mod := printf '%s\n'   ife.o | awk '!x[$$0]++ { print("net/ife/"$$0) }' > net/ife/ife.mod
