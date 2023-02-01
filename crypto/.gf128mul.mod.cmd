cmd_crypto/gf128mul.mod := printf '%s\n'   gf128mul.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/gf128mul.mod
