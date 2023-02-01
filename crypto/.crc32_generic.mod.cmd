cmd_crypto/crc32_generic.mod := printf '%s\n'   crc32_generic.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/crc32_generic.mod
