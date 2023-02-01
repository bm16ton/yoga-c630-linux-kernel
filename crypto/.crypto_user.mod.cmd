cmd_crypto/crypto_user.mod := printf '%s\n'   crypto_user_base.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/crypto_user.mod
