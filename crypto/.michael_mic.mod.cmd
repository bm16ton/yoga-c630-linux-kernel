cmd_crypto/michael_mic.mod := printf '%s\n'   michael_mic.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/michael_mic.mod
