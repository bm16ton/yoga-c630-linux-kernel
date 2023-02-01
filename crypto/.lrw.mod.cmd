cmd_crypto/lrw.mod := printf '%s\n'   lrw.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/lrw.mod
