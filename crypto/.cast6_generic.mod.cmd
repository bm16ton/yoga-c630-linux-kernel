cmd_crypto/cast6_generic.mod := printf '%s\n'   cast6_generic.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/cast6_generic.mod
