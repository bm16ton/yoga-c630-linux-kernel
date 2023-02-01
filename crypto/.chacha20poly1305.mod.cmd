cmd_crypto/chacha20poly1305.mod := printf '%s\n'   chacha20poly1305.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/chacha20poly1305.mod
