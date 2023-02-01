cmd_lib/crypto/libchacha.mod := printf '%s\n'   libchacha.o | awk '!x[$$0]++ { print("lib/crypto/"$$0) }' > lib/crypto/libchacha.mod
