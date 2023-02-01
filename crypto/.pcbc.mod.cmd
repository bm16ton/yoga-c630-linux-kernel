cmd_crypto/pcbc.mod := printf '%s\n'   pcbc.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/pcbc.mod
