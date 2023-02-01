cmd_crypto/essiv.mod := printf '%s\n'   essiv.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/essiv.mod
