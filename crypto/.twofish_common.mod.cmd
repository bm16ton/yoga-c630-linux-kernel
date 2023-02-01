cmd_crypto/twofish_common.mod := printf '%s\n'   twofish_common.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/twofish_common.mod
