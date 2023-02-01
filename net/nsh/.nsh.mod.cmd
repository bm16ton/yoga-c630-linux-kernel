cmd_net/nsh/nsh.mod := printf '%s\n'   nsh.o | awk '!x[$$0]++ { print("net/nsh/"$$0) }' > net/nsh/nsh.mod
