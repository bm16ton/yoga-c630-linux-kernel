cmd_crypto/seqiv.mod := printf '%s\n'   seqiv.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/seqiv.mod
