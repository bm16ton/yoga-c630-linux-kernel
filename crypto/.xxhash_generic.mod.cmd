cmd_crypto/xxhash_generic.mod := printf '%s\n'   xxhash_generic.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/xxhash_generic.mod
