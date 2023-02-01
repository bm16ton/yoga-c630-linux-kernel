cmd_crypto/algif_aead.mod := printf '%s\n'   algif_aead.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/algif_aead.mod
