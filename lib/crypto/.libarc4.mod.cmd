cmd_lib/crypto/libarc4.mod := printf '%s\n'   arc4.o | awk '!x[$$0]++ { print("lib/crypto/"$$0) }' > lib/crypto/libarc4.mod
