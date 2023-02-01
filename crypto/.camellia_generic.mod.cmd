cmd_crypto/camellia_generic.mod := printf '%s\n'   camellia_generic.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/camellia_generic.mod
