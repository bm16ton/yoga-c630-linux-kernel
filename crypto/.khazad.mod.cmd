cmd_crypto/khazad.mod := printf '%s\n'   khazad.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/khazad.mod
