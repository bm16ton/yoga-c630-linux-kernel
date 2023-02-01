cmd_crypto/ecdh_generic.mod := printf '%s\n'   ecdh.o ecdh_helper.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/ecdh_generic.mod
