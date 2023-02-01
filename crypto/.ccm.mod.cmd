cmd_crypto/ccm.mod := printf '%s\n'   ccm.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/ccm.mod
