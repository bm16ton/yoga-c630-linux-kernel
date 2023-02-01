cmd_crypto/drbg.mod := printf '%s\n'   drbg.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/drbg.mod
