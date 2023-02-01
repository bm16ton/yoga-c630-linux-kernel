cmd_crypto/algif_rng.mod := printf '%s\n'   algif_rng.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/algif_rng.mod
