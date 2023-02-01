cmd_crypto/jitterentropy_rng.mod := printf '%s\n'   jitterentropy.o jitterentropy-kcapi.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/jitterentropy_rng.mod
