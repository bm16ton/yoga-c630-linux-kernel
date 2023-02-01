cmd_crypto/async_tx/async_tx.mod := printf '%s\n'   async_tx.o | awk '!x[$$0]++ { print("crypto/async_tx/"$$0) }' > crypto/async_tx/async_tx.mod
