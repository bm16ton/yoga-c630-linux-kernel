cmd_crypto/twofish_generic.mod := printf '%s\n'   twofish_generic.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/twofish_generic.mod
