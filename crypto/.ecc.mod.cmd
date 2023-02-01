cmd_crypto/ecc.mod := printf '%s\n'   ecc.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/ecc.mod
