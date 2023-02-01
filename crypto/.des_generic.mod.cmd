cmd_crypto/des_generic.mod := printf '%s\n'   des_generic.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/des_generic.mod
