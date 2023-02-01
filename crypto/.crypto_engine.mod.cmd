cmd_crypto/crypto_engine.mod := printf '%s\n'   crypto_engine.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/crypto_engine.mod
