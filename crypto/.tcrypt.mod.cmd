cmd_crypto/tcrypt.mod := printf '%s\n'   tcrypt.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/tcrypt.mod
