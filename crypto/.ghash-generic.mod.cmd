cmd_crypto/ghash-generic.mod := printf '%s\n'   ghash-generic.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/ghash-generic.mod
