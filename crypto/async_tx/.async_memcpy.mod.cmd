cmd_crypto/async_tx/async_memcpy.mod := printf '%s\n'   async_memcpy.o | awk '!x[$$0]++ { print("crypto/async_tx/"$$0) }' > crypto/async_tx/async_memcpy.mod
