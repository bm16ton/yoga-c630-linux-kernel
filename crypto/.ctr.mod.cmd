cmd_crypto/ctr.mod := printf '%s\n'   ctr.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/ctr.mod
