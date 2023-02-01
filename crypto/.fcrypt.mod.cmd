cmd_crypto/fcrypt.mod := printf '%s\n'   fcrypt.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/fcrypt.mod
