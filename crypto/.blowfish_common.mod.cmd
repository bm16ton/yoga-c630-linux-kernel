cmd_crypto/blowfish_common.mod := printf '%s\n'   blowfish_common.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/blowfish_common.mod
