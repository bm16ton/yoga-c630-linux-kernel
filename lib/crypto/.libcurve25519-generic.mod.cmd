cmd_lib/crypto/libcurve25519-generic.mod := printf '%s\n'   curve25519-hacl64.o curve25519-generic.o | awk '!x[$$0]++ { print("lib/crypto/"$$0) }' > lib/crypto/libcurve25519-generic.mod
