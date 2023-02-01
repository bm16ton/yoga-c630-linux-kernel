cmd_crypto/async_tx/async_raid6_recov.mod := printf '%s\n'   async_raid6_recov.o | awk '!x[$$0]++ { print("crypto/async_tx/"$$0) }' > crypto/async_tx/async_raid6_recov.mod
