cmd_lib/crypto/libdes.mod := printf '%s\n'   des.o | awk '!x[$$0]++ { print("lib/crypto/"$$0) }' > lib/crypto/libdes.mod
