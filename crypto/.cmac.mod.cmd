cmd_crypto/cmac.mod := printf '%s\n'   cmac.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/cmac.mod
