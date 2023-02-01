cmd_crypto/async_tx/async_pq.mod := printf '%s\n'   async_pq.o | awk '!x[$$0]++ { print("crypto/async_tx/"$$0) }' > crypto/async_tx/async_pq.mod
