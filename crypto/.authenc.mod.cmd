cmd_crypto/authenc.mod := printf '%s\n'   authenc.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/authenc.mod
