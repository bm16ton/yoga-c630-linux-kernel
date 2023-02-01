cmd_crypto/serpent_generic.mod := printf '%s\n'   serpent_generic.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/serpent_generic.mod
