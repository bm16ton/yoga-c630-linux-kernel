cmd_crypto/seed.mod := printf '%s\n'   seed.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/seed.mod
