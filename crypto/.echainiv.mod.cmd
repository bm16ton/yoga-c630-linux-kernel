cmd_crypto/echainiv.mod := printf '%s\n'   echainiv.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/echainiv.mod
