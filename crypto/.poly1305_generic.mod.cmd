cmd_crypto/poly1305_generic.mod := printf '%s\n'   poly1305_generic.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/poly1305_generic.mod
