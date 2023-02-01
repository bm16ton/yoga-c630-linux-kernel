cmd_crypto/ansi_cprng.mod := printf '%s\n'   ansi_cprng.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/ansi_cprng.mod
