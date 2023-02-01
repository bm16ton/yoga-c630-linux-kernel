cmd_crypto/gcm.mod := printf '%s\n'   gcm.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/gcm.mod
