cmd_crypto/vmac.mod := printf '%s\n'   vmac.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/vmac.mod
