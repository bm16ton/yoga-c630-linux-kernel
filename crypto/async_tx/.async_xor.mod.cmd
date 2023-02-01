cmd_crypto/async_tx/async_xor.mod := printf '%s\n'   async_xor.o | awk '!x[$$0]++ { print("crypto/async_tx/"$$0) }' > crypto/async_tx/async_xor.mod
