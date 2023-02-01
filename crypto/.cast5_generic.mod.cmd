cmd_crypto/cast5_generic.mod := printf '%s\n'   cast5_generic.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/cast5_generic.mod
