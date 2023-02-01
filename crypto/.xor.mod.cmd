cmd_crypto/xor.mod := printf '%s\n'   xor.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/xor.mod
