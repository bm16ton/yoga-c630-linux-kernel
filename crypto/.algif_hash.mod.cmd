cmd_crypto/algif_hash.mod := printf '%s\n'   algif_hash.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/algif_hash.mod
