cmd_crypto/cast_common.mod := printf '%s\n'   cast_common.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/cast_common.mod
