cmd_crypto/af_alg.mod := printf '%s\n'   af_alg.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/af_alg.mod
