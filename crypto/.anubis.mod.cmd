cmd_crypto/anubis.mod := printf '%s\n'   anubis.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/anubis.mod
