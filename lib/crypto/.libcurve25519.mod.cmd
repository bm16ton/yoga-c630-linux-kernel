cmd_lib/crypto/libcurve25519.mod := printf '%s\n'   curve25519.o | awk '!x[$$0]++ { print("lib/crypto/"$$0) }' > lib/crypto/libcurve25519.mod
