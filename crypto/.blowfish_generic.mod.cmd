cmd_crypto/blowfish_generic.mod := printf '%s\n'   blowfish_generic.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/blowfish_generic.mod
