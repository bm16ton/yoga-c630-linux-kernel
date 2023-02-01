cmd_crypto/wp512.mod := printf '%s\n'   wp512.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/wp512.mod
