cmd_crypto/sha3_generic.mod := printf '%s\n'   sha3_generic.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/sha3_generic.mod
