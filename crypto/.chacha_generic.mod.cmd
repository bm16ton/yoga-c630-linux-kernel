cmd_crypto/chacha_generic.mod := printf '%s\n'   chacha_generic.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/chacha_generic.mod
