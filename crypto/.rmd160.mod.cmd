cmd_crypto/rmd160.mod := printf '%s\n'   rmd160.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/rmd160.mod
