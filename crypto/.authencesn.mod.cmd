cmd_crypto/authencesn.mod := printf '%s\n'   authencesn.o | awk '!x[$$0]++ { print("crypto/"$$0) }' > crypto/authencesn.mod
