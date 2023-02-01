cmd_lib/crypto/libpoly1305.mod := printf '%s\n'   poly1305-donna64.o poly1305.o | awk '!x[$$0]++ { print("lib/crypto/"$$0) }' > lib/crypto/libpoly1305.mod
