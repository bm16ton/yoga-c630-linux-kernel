cmd_crypto/algif_skcipher.mod := printf '%s\n'   algif_skcipher.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/algif_skcipher.mod
