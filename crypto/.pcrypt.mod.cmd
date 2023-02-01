cmd_crypto/pcrypt.mod := printf '%s\n'   pcrypt.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/pcrypt.mod
