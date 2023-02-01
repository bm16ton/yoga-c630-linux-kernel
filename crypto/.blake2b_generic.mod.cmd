cmd_crypto/blake2b_generic.mod := printf '%s\n'   blake2b_generic.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/blake2b_generic.mod
