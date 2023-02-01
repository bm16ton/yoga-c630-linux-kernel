cmd_crypto/xcbc.mod := printf '%s\n'   xcbc.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/xcbc.mod
