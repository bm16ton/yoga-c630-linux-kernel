cmd_net/unix/unix_diag.mod := printf '%s\n'   diag.o | awk '!x[$$0]++ { print("net/unix/"$$0) }' > net/unix/unix_diag.mod
